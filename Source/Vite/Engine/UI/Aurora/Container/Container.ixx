export module Vite.Aurora.Container;

import Vite.Core;
import Vite.FontRenderer;
import Vite.Aurora.Component;
import Vite.Aurora.Controls;

export namespace Hedron::UI {

class Container: public Component {
public:
    Container(const string &id, const ComponentType &type = ComponentType::Container):
        Component(id, type) {}
    virtual ~Container() = default;

    // Accessors
    Component *GetChild(const string &id) {
        if (*this == id) return this;
        for (const auto &child : mChildren) {
            if (child->Type < ComponentType::Containers) {
                if (auto *const result = child->As<Container>()->GetChild(id)) {
                    return result;
                }
            } else {
                if (*child == id) {
                    return child.get();
                }
            }
        }
        return nullptr;
    }
    const vector<Scope<Component>> &GetChildren() {
        return mChildren;
    }

    // Mutators
    void AddChild(Scope<Component> child) {
        child->Parent = this;
        mChildren.push_back(std::move(child));
    }

    // Factory Methods
    Container *CreateContainer(const UI::Layout &layout = Layout::None, const string &uniqueId = "", const ComponentType &type = ComponentType::Container) {
        string id = uniqueId.empty() ? std::format("Container#{}", sContainerCounter++) : uniqueId;

        auto *component = GetChild(id);
        if (component) return component->As<Container>();

        auto container = CreateScope<Container>(id, type);
        container->Layout = layout;
        container->Expand = true;
        container->MaxSize = { 1e30f, 1e30f };
        container->Spacing = this->Style.Spacing;
        container->Style.Font = this->Style.Font;
        switch (layout) {
            case Layout::Stack:
                container->Stretch = { 1.0f, 1.0f };
                break;
            case Layout::Vertical:
                container->Stretch = { 1.0f, 0.0f };
                break;
            case Layout::Horizontal:
                container->Stretch = { 0.0f, 1.0f };
                break;
        }

        auto result = container.get();
        AddChild(std::move(container));
        Parent = this;
        return result;
    }
    Container *CreateScrollView(float maxHeight) {
        string id = std::format("ScrollView#{}", sScrollViewCounter);

        auto *component = GetChild(id);
        if (component) {
            sScrollViewCounter++;
            return component->As<Container>();
        }

        auto scrollview = CreateContainer(Layout::Vertical, id, ComponentType::ScrollView);
        scrollview->Clip = true;
        scrollview->Expand = false;
        scrollview->Padding = { 6.0f, 6.0f, 6.0f, 6.0f };
        scrollview->Stretch = { 1.0f, 1.0f };
        scrollview->Spacing = 2.0f;
        scrollview->MaxSize.Height = maxHeight;

        // ToDo: ScrollBar currently missing...

        sScrollViewCounter++;
        return scrollview;
    }

    Button *CreateButton(string_view text) {
        string id = std::format("Button#{}", sButtonCounter++);
        auto *component = GetChild(id)->As<Button>();
        if (component) return component;

        auto button = Control::Create<Button>(id, string(text));
        button->Parent = this;
        button->Color = this->Style.ColorText;
        button->Font = this->Style.Font.get();
        button->Update();

        auto result = button.get();
        AddChild(std::move(button));
        return result;
    }
    CheckBox *CreateCheckBox(string_view text, bool value = false) {
        string id = std::format("CheckBox#{}", sCheckBoxCounter++);
        auto *component = GetChild(id);
        if (component) return component->As<CheckBox>();

        auto checkbox = Control::Create<CheckBox>(id, text, value);
        checkbox->Parent = this;
        checkbox->Color = this->Style.ColorText;
        checkbox->Font = this->Style.Font.get();
        checkbox->OutherColor = this->Style.ColorFrame;
        checkbox->InnerColor = this->Style.ColorPrimary;
        checkbox->Update();

        auto result = checkbox.get();
        AddChild(std::move(checkbox));
        return result;
    }
    Image *CreateImage(string_view path) {
        string id = std::format("Image#{}", sImageCounter++);

        auto *component = GetChild(id);
        if (component) return component->As<Image>();

        auto image = Control::Create<Image>(id);
        image->Parent = this;
        image->Stretch = { 1.0f, 1.0f };
        image->Data = Texture::Create({}, string(path));

        auto result = image.get();
        AddChild(std::move(image));
        return result;
    }
    InputBox *CreateInputBox(string_view text) {
        string id = std::format("Input#{}", sInputBoxCounter++);

        auto *component = GetChild(id)->As<InputBox>();
        if (component) return component;

        auto input = Control::Create<InputBox>(id, string(text));
        input->Parent = this;
        input->Color = this->Style.ColorText;
        input->Font = this->Style.Font.get();
        input->Update();

        auto result = input.get();
        AddChild(std::move(input));
        return result;
    }
    Label *CreateLabel(string_view text, Font *font = nullptr, const string &uniqueId = "") {
        string id = uniqueId.empty() ? std::format("Label#{}", sLabelCounter++) : uniqueId;

        auto *component = GetChild(id);
        if (component) return component->As<Label>();

        auto label = Control::Create<Label>(id, text);
        label->Parent = this;
        label->Color = this->Style.ColorText;
        if (font) {
            label->Font = font;
        } else {
            label->Font = this->Style.Font.get();
        }
        label->Update();

        auto result = label.get();
        AddChild(std::move(label));
        return result;
    }
    Selection *CreateSelection(string_view text, const vector<string> &options) {
        string id = std::format("Selection#{}", sSelectionCounter++);

        auto *component = GetChild(id)->As<Selection>();
        if (component) return component;

        auto selection = Control::Create<Selection>(id, text, options);
        selection->Parent = this;
        selection->Color = this->Style.ColorText;
        selection->Font = this->Style.Font.get();
        selection->Update();

        auto result = selection.get();
        AddChild(std::move(selection));
        return result;
    }
    Seperator *CreateSeperator() {
        string id = std::format("Seperator#{}", sSeperatorCounter++);
        auto *component = GetChild(id)->As<Seperator>();
        if (component) return component;

        auto seperator = Control::Create<Seperator>(id);
        seperator->Parent = this;
        seperator->Update();

        auto result = seperator.get();
        AddChild(std::move(seperator));
        return result;
        // ToDo: Check also line shader "vertex/ui" "fragment/ui/line"
        // ToDo: Additive BlendMode
    }
    Slider *CreateSlider(float value, float min = 0.0f, float max = 128.0f) {
        string id = std::format("Slider#{}", sSliderCounter++);

        auto *component = GetChild(id);
        if (component) return component->As<Slider>();

        auto slider = Control::Create<Slider>(id, value, min, max);
        slider->Parent = this;

        auto result = slider.get();
        AddChild(std::move(slider));
        return result;
    }

    // Methods

    // Check if a container and its child at position is hovered
    bool Focused(const Position2D position) {
        Reset();
        for (auto &child : mChildren | std::views::reverse) {
            if (child->Hovered(position)) {
                if (child->Type < ComponentType::Containers) {
                    if (child->As<Container>()->Focused(position)) return true;
                }
                if (!child->Interactive) return false;
                child->Focused = true;
                Log("{}\n", child->ID);
                return true;
            }
        }
        return false;
    }

    // Compute the size of the container based on its children
    void ComputeSize() {
        // Calculate the minimum size for each child
        for (const auto &child : mChildren) {
            if (child->Type < ComponentType::Containers) {
                child->As<Container>()->ComputeSize();
            }
        }
        MinSize = { 0.0f, 0.0f };

        // Calculate the minimum size of the current container based on its children
        for (const auto &child : mChildren) {
            switch (Layout) {
                // For stacking layout, choose the maximum width and height among children
                case Layout::Stack: {
                    MinSize.Width = std::max(MinSize.Width, child->MinSize.Width);
                    MinSize.Height = std::max(MinSize.Height, child->MinSize.Height);
                    break;
                }
                // For vertical layout, add up children's heights and choose maximum width
                case Layout::Vertical: {
                    MinSize.Width = std::max(MinSize.Width, child->MinSize.Width);
                    MinSize.Height += child->MinSize.Height;
                    if (child != mChildren.front()) MinSize.Height += Spacing;
                    break;
                }
                // For horizontal layout, add up children's widths and choose maximum height
                case Layout::Horizontal: {
                    MinSize.Width += child->MinSize.Width;
                    MinSize.Height = std::max(MinSize.Height, child->MinSize.Height);
                    if (child != mChildren.front()) MinSize.Width += Spacing;
                    break;
                }
            }
        }

        // Add padding to the minimum size
        MinSize.Width += Padding.Left + Padding.Right;
        MinSize.Height += Padding.Top + Padding.Bottom;

        // Clamp the calculated minimum size to the specified maximum size
        OriginalSize = MinSize;
        MinSize.Width = std::min(MinSize.Width, MaxSize.Width);
        MinSize.Height = std::min(MinSize.Height, MaxSize.Height);
    }

    // Compute the position of the container and update its children
    void ComputePosition() {
        auto pos = Position;
        auto size = Size;
        auto extra = 0.0f;
        auto totalStretch = 0.0f;

        // Adjust the position and size for padding and offset
        pos.X += Offset.X + Padding.Left;
        pos.Y += Offset.Y + Padding.Top;
        size.Width -= Padding.Left + Padding.Right;
        size.Height -= Padding.Top + Padding.Bottom;

        // Calculate extra space and total stretch based on expand settings
        if (Expand) {
            if (Layout == Layout::Vertical) {
                extra = Size.Height - MinSize.Height;
                for (auto &child : mChildren) {
                    totalStretch += child->Stretch.Y;
                }
            } else if (Layout == Layout::Horizontal) {
                extra = Size.Width - MinSize.Width;
                for (auto &child : mChildren) {
                    totalStretch += child->Stretch.X;
                }
            }
        }

        // Distribute extra space among stretched children
        if (totalStretch > 0.0f) extra /= totalStretch;

        auto s { 0.0f };
        for (auto &child : mChildren) {
            switch (Layout) {
                case Layout::None: {
                    child->CalculateLayout(child->Position, size);
                    break;

                }
                case Layout::Stack: {
                    child->CalculateLayout(pos, size);
                    break;
                }

                // Calculate height based on child's minimum size and stretch factor, than update childs position and size, move the position for the next child vertically
                case Layout::Vertical: {
                    s = child->MinSize.Height;
                    if (extra > 0) s += child->Stretch.Y * extra;
                    child->CalculateLayout(pos, { size.Width, s });
                    pos.Y += child->Size.Height + Spacing;
                    break;
                }

                // Calculate height based on child's minimum size and stretch factor, than update childs position and size, move the position for the next child horizontally
                case Layout::Horizontal: {
                    s = child->MinSize.Width;
                    if (extra > 0) s += child->Stretch.X * extra;
                    child->CalculateLayout(pos, { s, size.Height });
                    pos.X += child->Size.Width + Spacing;
                    break;
                }
            }

            // Recursively layout child containers or windows
            if (child->Type < ComponentType::Containers) child->As<Container>()->ComputePosition();
        }
    }

    // Draw the container and its children
    void Draw() override;
//
    void DebugPrint(size_t level = 0) const {
        Log("{}{}{} [ childs: {} | Position: 'x={}, y={}' | Size '{}x{}' ]\n",
            level == 0 ? "" : string(level * 2 - 2, ' '),
            level == 0 ? "" : "◌ ", ID,
            mChildren.size(),
            Position.X, Position.Y,
            Size.Width, Size.Height
        );
        for (const auto &child : mChildren) {
            if (child->Type < ComponentType::Containers) {
                child->As<Container>()->DebugPrint(level + 1);
            } else {
                child->As<Control>()->DebugPrint(level);
            }
        }
    }
    void MoveToTop(const string &id) {
        auto it = std::find_if(mChildren.begin(), mChildren.end(), [&id](const auto &child) {
            return child->ID == id;
        });
        if (it != mChildren.end()) {
            std::rotate(it, mChildren.end() - 1, mChildren.end());
        }
    }
    static void Update() {
        sContainerCounter = 0;
        sButtonCounter = 0;
        sCheckBoxCounter = 0;
        sImageCounter = 0;
        sInputBoxCounter = 0;
        sLabelCounter = 0;
        sScrollViewCounter = 0;
        sSelectionCounter = 0;
        sSeperatorCounter = 0;
        sSliderCounter = 0;
    }


private: // Methods
    void Reset() {
        for (auto &child : mChildren) {
            child->Focused = false;
            if (child->Type < ComponentType::Containers) {
                child->As<Container>()->Reset();
            }
        }
    }
    void UpdateClipRect() {
        //ClipRect.Right = Position.X;
        //ClipRect.Bottom = Position.Y;

        //?rect->Upper = { g->Position, g->Size };

        //ClipRect->Left = std::min(rect->Upper.X, rect->Previous->Upper.X);
        //ClipRect->Top = std::min(rect->Upper.Y, rect->Previous->Upper.Y);
        //ClipRect->Right = std::max(rect->Lower.Y, rect->Previous->Lower.Y);
        //ClipRect->Bottom = std::max(rect->Lower.X, rect->Previous->Lower.X);
    }

public: // Properties
    bool Clip {};
    bool Expand { true };
    Layout Layout {};
    Size2D MaxSize { 1e30f, 1e30f };
    float Spacing {};
    Style Style {};
    float ZIndex {};

private: // Properties
    vector<Scope<Component>> mChildren;

private: // States
    inline static size_t sContainerCounter {};
    inline static size_t sWindowCounter {};

    inline static size_t sButtonCounter {};
    inline static size_t sCheckBoxCounter {};
    inline static size_t sImageCounter {};
    inline static size_t sInputBoxCounter {};
    inline static size_t sLabelCounter {};
    inline static size_t sScrollViewCounter {};
    inline static size_t sSelectionCounter {};
    inline static size_t sSeperatorCounter {};
    inline static size_t sSliderCounter {};
};

}
