export module Vite.Aurora;

import Vite.Aurora.Components;
import Vite.Core;
import Vite.FontRenderer;
import Vite.Renderer.Texture;
import Vite.Renderer.Viewport;
import Vite.UIRenderer;

///
/// @brief Enumeration and Types
///

///
/// @brief Private
///
namespace Hedron::UI {

///
/// Tests
///

using CheckListEntry = std::map<std::string, bool>;
using CheckList = std::map<std::string, CheckListEntry>;

CheckList gCheckList = {
    { "Basic Widgets", {
        { "Hash Storage Invalidation", false },
        { "Text", true },
        { "Buttons", true },
        { "Checkboxes", true },
        { "Sliders", false },
        { "Radio Groups", false },
        { "Selectable", false },
        { "Tooltips", false },
    }},
    { "Layout", {
        { "Deferred Layout Pass", true },
        { "Horizontal Groups", true },
        { "Vertical Groups", true },
        { "Stacked Groups", true },
        { "Group Padding", true },
        { "Group Margins", false },
        { "Child Spacing ", true },
        { "ScrollViews", true },
        { "Windows", true },
    }},
    { "Input", {
        { "Clip Groups", true },
        { "Input Clipping", true },
        { "Sticky Drag", false },
        { "Keyboard Navigation", false },
        { "Gamepad Navigation", false },
    }},
    { "Draw", {
        { "Draw Layers", true },
        { "Shader-Based Render", true },
        { "Glyph Render", false },
        }},
    { "Technical", {
        { "Hash Storage", true },
        { "Hash Storage Invalidation", false },
        { "Deferred Metrics", true },
    }},
};

constexpr const char *gCodeExample = R"(
#include <print>

// The amazing and well known foo class.
class Foo {
public:
    Foo() = default;
    virtual ~Foo() = default;

    virtual void Update() = 0;
};

// As amazing as foo can be, it is nothing without Bar.
class Bar: Foo {
public:
    Bar() = default;
    virtual ~Bar() = default;

    void Update() override {
    }
};


int main() {
    print("{}", "Hello World!");
}
)";

///
/// @brief This class manages the GUI layout.
///
class UILayoutManager {
public:
    UILayoutManager():
        mRoot(CreateScope<Container>("Root")) {
    }
    ~UILayoutManager() = default;

    // Accessors
    Container *GetRoot() {
        return mRoot.get();
    }
    Component *GetComponent(const string &id) {
        auto element = mRoot->GetChild(id);
        return element;
    }

    // Methods
    //Window *CreateWindow(string_view title, const string &uniqueId = "") {
    //    string id = uniqueId.empty() ? std::format("Window#{}", sWindowCounter++) : uniqueId;
    //    auto *component = GetChild(id);
    //    if (component) return component->As<Window>();
    //}
    void AddContainer(Scope<Container> id) {
        mRoot->AddChild(std::move(id));
    }
    void CalculateLayout() {
        mRoot->ComputeSize();
        mRoot->ComputePosition();
    }
    void DebugPrint(size_t level = 0) {
        mRoot->DebugPrint(level);
    }

private:
    Scope<Container> mRoot;
    unordered_map<string, Component> mComponents {};
};

}

///
/// @brief Public
///
export namespace Hedron::UI {

///
/// @brief Hybrid-Mode-GUI, a combination of immediate mode and retained mode.
/// It's simple but effective and has a built-in automatic layout system.
/// @note This implementation is inspired by Josh Parnell
/// @link http://forums.ltheory.com/viewtopic.php?t=6582
///
class Aurora: public SteadyObject {
private:
    // Friends
    friend Container;
    friend Window;
    friend Button;
    friend CheckBox;
    friend ColorPicker;
    friend InputBox;
    friend Label;
    friend Selection;
    friend Slider;
    friend Seperator;
    friend Tree;

private:
    // Constructors and Destructor
    Aurora() {
        mUILayout = CreateScope<UILayoutManager>();
        auto root = mUILayout->GetRoot();

        root->Active = Input::GetMouseButtonState(MouseButton::Left);
        root->Clip = true;
        root->Position = { 0.0f, 0.0f };
        root->Size = { 1280.0f, 1024.0f };
        root->Style.Font = CreateReference<Font>("Rajdhani-Regular", 14);

        mViewport = Viewport::Create({ 0, 0, 1280, 1024 });

        mFontExo2Bold = CreateScope<Font>("Exo2-Bold", 30);
        mFontFiraMono = CreateScope<Font>("FiraMono", 10);
        mFontRajdhani = CreateScope<Font>("Rajdhani-Regular", 18);
    };
    ~Aurora() = default;

    // Global Instance
    static Aurora &Instance() {
        static Aurora instance;
        return instance;
    }

    // Accessors
    static Scope<UILayoutManager> &GetLayoutManager() { return Instance().mUILayout; }
    static Container *GetRoot() { return Instance().mUILayout->GetRoot(); }
    static Style &GetStyle() { return Instance().mUILayout->GetRoot()->Style; }

public:
    /// @brief Creates a window or returns an existing window
    /// @param title Specify the window title.
    /// @return Returns a non owning pointer to the object.
    static Container *CreateWindow(string_view title) {
        string id = std::format("Window#{}", sWindowCounter);

        auto &manager = Instance().mUILayout;
        auto *component = manager->GetComponent(id);
        if (component) {
            sWindowCounter++;
            return component->As<Container>();
        }

        // Container
        auto window = CreateScope<Window>(id, title);
        window->Layout = Layout::Vertical;
        window->Expand = true;
        window->FrameOpacity = 0.97f;
        window->Padding = { 8.0f, 0.0f, 8.0f, 8.0f };
        window->Style.Font = manager->GetRoot()->Style.Font;

        // TitleBar
        auto titleBarId = std::format("TitleBar#{}", sWindowCounter);
        auto titleBar = window->CreateContainer(Layout::Stack, titleBarId);
        titleBar->Clip = true;
        titleBar->Interactive = false;
        titleBar->Padding = { 8.0f, 8.0f, 8.0f, 8.0f };
        titleBar->Stretch = { 1.0f, 1.0f };

        auto titleLabelId = std::format("TitleLabel#{}", sWindowCounter);
        auto titleLabel = titleBar->CreateLabel(title, nullptr, titleLabelId);
        titleLabel->Color = { 1.0f, 1.0f, 1.0f, 0.3f };
        titleLabel->Alignment = { 0.5f, 0.5f };

        auto *result = window.get();
        manager->AddContainer(std::move(window));
        sWindowCounter++;
        return result;
    }

    // Draws the GUI
    static void Draw() {
        UIRenderer::Begin(Instance().mViewport);
        GetRoot()->Draw();
        UIRenderer::End();
        UIRenderer::Draw();
    }
    static void Update(DeltaTime deltaTime) {
        // Calculate Frames
        mFrames++;
        mDeltaDelay += deltaTime;

        // Update Inputs
        if (mDeltaDelay > 0.016333f) {
            auto [mouseX, mouseY] = Input::GetMousePosition();
            sInputState.LastMousePosition = { mouseX, mouseY };

            sInputState.MouseClicked = Input::GetMouseButtonStateDelta(MouseButton::Left);
            sInputState.MousePressed = Input::GetMouseButtonState(MouseButton::Left);

            // Start Dragging
            if (sInputState.MouseClicked && sInputState.MousePressed) {
                sInputState.Dragging = true;
                sInputState.DragStartPosition.X = mouseX;
                sInputState.DragStartPosition.Y = mouseY;
            }

            // Update Dragging
            if (sInputState.MousePressed) {
                sInputState.DragCurrentPosition.X = mouseX - sInputState.DragStartPosition.X;
                sInputState.DragCurrentPosition.Y = mouseY - sInputState.DragStartPosition.Y;
            } else {
                sInputState.Dragging = false;
                sInputState.DragStartPosition = {};
                sInputState.DragCurrentPosition = {};
            }
        }

        // Update Information
        if (mDeltaDelay > 1.0f) {
            mFPS = mFrames;
            mMSPF = 1000.0 / mFrames;
            mFrames = 0;
            mDeltaDelay = 0;
        }

        // Update Initial Layout
        if (static bool once = true) {
            GetLayoutManager()->CalculateLayout();
            GetLayoutManager()->GetRoot()->DebugPrint();
            once = false;
        }

        // Check if component is active (hovered and on top)
        if (!sInputState.Dragging) {
            GetRoot()->Focused(sInputState.LastMousePosition);
        }

        sWindowCounter = 0;
        Container::Update();
    }

    // Shows some demo windows and is also used for tests
    static void ShowDemo() {
        #pragma warning(disable: 4189)
        ///
        /// @brief Here we test new API styles, until we find the best one...
        ///

        // Background
        auto image = Aurora::GetRoot()->CreateImage("Assets/Textures/Wallpaper.jpg");
        //auto image = HmGui::GetRoot()->CreateImage("Data/Cache/Fonts/Rajdhani.bmp");
        image->Interactive = false;

        //
        // Simple Window Test
        //
        {
            auto window = CreateWindow("This is a test Window!");
            window->Alignment = { 0.5f, 0.5f };

            // TabBar
            {
                auto tabs = window->CreateContainer(Layout::Horizontal);
                tabs->Stretch = { 1.0f, 1.0f };

                auto tabsButtonLeft = tabs->CreateButton(" < ");
                tabsButtonLeft->Stretch = { 0.0f, 1.0f };
                auto tabsButton1 = tabs->CreateButton(" Tab1 ");
                auto tabsButton2 = tabs->CreateButton(" Tab2 ");
                auto tabsButton3 = tabs->CreateButton(" Tab3 ");
                auto tabsButtonRight = tabs->CreateButton(" > ");
                tabsButtonRight->Stretch = { 0.0f, 1.0f };
            }

            // Buttons and CheckBoxes
            {
                auto buttons = window->CreateContainer(Layout::Horizontal);
                buttons->Stretch = { 1.0f, 0.0f };

                // Column A
                {
                    auto group = buttons->CreateContainer(Layout::Vertical);
                    group->Padding = { 4.0f, 8.0f, 4.0f, 8.0f };
                    group->Stretch = { 1.0f, 1.0f };

                    auto welcome = group->CreateLabel("Welcome to...");
                    welcome->Alignment = { 0.5f, 0.5f };

                    auto caption = group->CreateLabel("~ Hybrid Mode ~", Instance().mFontExo2Bold.get());
                    caption->Color = { 1.0f, 0.0f, 0.3f, 1.0f };
                    caption->Alignment = { 0.5f, 0.5f };

                    auto subscript = group->CreateLabel("GUI");
                    subscript->Alignment = { 0.5f, 0.5f };

                    auto buttonNotSoStretchy = group->CreateButton("Not-So-Stretchy");
                    buttonNotSoStretchy->Stretch = { 1.0f, 0.0f };
                    auto buttonStretchy = group->CreateButton("Stretchy");
                    buttonStretchy->Stretch = { 1.0f, 1.0f };

                    auto subGroup = group->CreateContainer(Layout::Horizontal);
                    subGroup->Stretch = { 1.0f, 1.0f };
                    for (auto i = 1; i < 3; i++) {
                        auto innerGroup = subGroup->CreateContainer(Layout::Vertical);
                        innerGroup->Stretch = { 1.0f, 1.0f };
                        for (auto j = 1; j < 3; j++) {
                            auto button = innerGroup->CreateButton(":)");
                        }
                    }
                }

                // Column B
                {
                    auto group = buttons->CreateContainer(Layout::Vertical);
                    //group->Alignment = { 0.0f, 1.0f };
                    group->Padding = { 4.0f, 8.0f, 4.0f, 8.0f };
                    group->Stretch = { 1.0f, 1.0f };

                    auto eventButton = group->CreateButton("-- OPT 1 --");
                    eventButton->Click = [&]() {
                        Log("Button '-- OPT 1 --' clicked!\n");
                    };

                    auto silentButton = group->CreateButton("-- OPT 2 --");

                    auto checkBoxA = group->CreateCheckBox("Yas", true);
                    auto checkBoxB = group->CreateCheckBox("Nope", false);
                    auto checkBoxC = group->CreateCheckBox("Possibly?", false);

                    auto doneButton = group->CreateButton("DONE");
                }

                // Column C
                {
                    auto group = buttons->CreateContainer(Layout::Vertical);
                    group->Padding = { 4.0f, 8.0f, 4.0f, 8.0f };
                    group->Stretch = { 1.0f, 1.0f };

                    for (auto i = 1; i < 9; i++) {
                        auto autoGroup = group->CreateContainer(Layout::Horizontal);
                        autoGroup->Alignment = { 0.5f, 0.5f };

                        for (auto j = 1; j < i; j++) {
                            auto result = std::format("{}.{}", i, j);
                            auto button = autoGroup->CreateButton(result);
                        }
                    }

                }

                // Column D
                {
                    auto view = buttons->CreateScrollView(256.0f);
                    view->Spacing = 8.0f;
                    for (auto &[entry, list] : gCheckList) {
                        auto caption = view->CreateLabel(entry, Instance().mFontRajdhani.get());
                        caption->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
                        auto group = view->CreateContainer(Layout::Vertical);
                        group->Spacing = 2.0f;
                        group->Padding.Left = 12.0f;
                        for (auto &[key, value] : list) {
                            auto check = group->CreateCheckBox(key, value);
                        }
                    }
                }
            }

            // Editor
            {
                auto editorTitle = window->CreateLabel("水 Behöld, the codez! \\o/");
                auto editors = window->CreateContainer(Layout::Horizontal);
                editors->Stretch = { 1.0f, 1.0f };
                for (auto i = 0; i < 2; i++) {
                    auto scrollView = editors->CreateScrollView(200);
                    auto lines = String::Split(gCodeExample, '\n');
                    for (auto &line : lines) {
                        auto text = scrollView->CreateLabel(line, Instance().mFontFiraMono.get());
                        text->Color = { 0.1f, 0.5f, 1.0f, 1.0f };
                    }
                }
            }
        }

        //
        // ToDo List Window
        //
        {
            auto window = CreateWindow("ToDo List");
            window->Alignment = { 1.0f, 0.0f };

            auto view = window->CreateScrollView(256.0f);
            view->Spacing = 8.0f;
            for (auto &[entry, list] : gCheckList) {
                auto caption = view->CreateLabel(entry, Instance().mFontRajdhani.get());
                caption->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
                auto group = view->CreateContainer(Layout::Vertical);
                group->Spacing = 2.0f;
                group->Padding.Left = 12.0f;
                for (auto &[key, value] : list) {
                    auto check = group->CreateCheckBox(key, value);
                }
            }
        }

        //
        // Metrics Window
        //
        {
            auto window = CreateWindow("Metrics");
            window->Alignment = { 1.0f, 1.0f };

            auto container = window->CreateContainer(Layout::Vertical);
            container->Alignment = { 1.0f, 1.0f };

            auto caption = container->CreateLabel("Application Statistics");
            auto fps = container->CreateLabel("frames/s: ####.##");
            fps->Text = std::format("frames/s: {:.2f}", mFPS);
            auto msf = container->CreateLabel("ms/Frame: ####.##");
            msf->Text = std::format("ms/Frame: {:.2f}", mMSPF);
        }

        // Under Construction Window
        {
            auto window = Aurora::CreateWindow("Under Construction");
            window->Alignment = { 0.0f, 1.0f };

            auto container = window->CreateContainer(Layout::Vertical);
            container->Alignment = { 0.5f, 0.5f };

            auto input = container->CreateInputBox("Type in your text...");
            input->MinSize = { 200.0f, 64.0f };

            auto slider = container->CreateSlider(0.5f, 0.0f, 1.0f);
            slider->MinSize = { 200.0f, 20.0f };

            auto seperator = container->CreateSeperator();
            //seperator->Size = { 300.0f, 2.0f };

            auto selection = container->CreateSelection("Select a Option", { "A", "B", "C" });
            selection->Click = [&](const string &option = "") {
                Log("Selected option: {}\n", option);
            };
        }

        #pragma warning(default: 4189)
    }

private:
    // Counter for ComponentIDs
    inline static size_t sWindowCounter {};

    // Instances
    Scope<UILayoutManager> mUILayout {};
    Scope<Viewport> mViewport;

    // States
    struct InputState {
        bool Dragging {};
        bool MouseClicked {};
        bool MousePressed {};

        Position2D DragStartPosition {};
        Position2D DragCurrentPosition {};
        Position2D LastMousePosition {};
    } inline static sInputState {};

    // Test
    Scope<Font> mFontExo2Bold = nullptr;
    Scope<Font> mFontFiraMono = nullptr;
    Scope<Font> mFontRajdhani = nullptr;
    inline static thread_local double mFrames {};
    inline static thread_local double mFPS {};
    inline static thread_local double mMSPF {};
    inline static thread_local double mDeltaDelay {};
};

}
