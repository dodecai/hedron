export module Vite.DearImGui.Layer;

export import <imgui/imgui.h>;
//export import Vite.Bridge.DearImGui;
import Vite.App.Layers;
import Vite.Core;

export namespace Hedron {

class DearImGuiLayer: public Layer {
public:
    /// Default
    DearImGuiLayer();
    virtual ~DearImGuiLayer();

    /// Controls
    virtual void Attach() override;
    virtual void Detach() override;
    virtual void Update(DeltaTime deltaTime) override;
    virtual void UpdateUI() override;
    void Prepare();
    void Render();

    /// Events
    virtual void OnAppEvent(const WindowEvent &event) override;
    virtual void OnInputEvent(const ControllerEvent &event) override;
    virtual void OnInputEvent(const KeyboardEvent &event) override;
    virtual void OnInputEvent(const MouseEvent &event) override;
    virtual void OnInputEvent(const TouchEvent &event) override;

private:
    /// Properties
    const float mFontSize = 16.0f;
    string mConfigFile = "./Data/DearImGui.ini";
    string mLogFile = "./Log/DearImGui.log";
    bool mShowDemoWindow = false;
};

/// Helpers
namespace UI {

//// Labels
//template <typename ... Args>
//auto Label(const string &format, const Args &...arguments) {
//    ImGui::Text(format.c_str(), arguments...);
//}
//
//template <typename ... Args>
//auto LabelX(const string &format, const Args &...arguments) {
//    ((ImGui::Text(format.c_str(), arguments)), ...);
//}
//
//
///**
//* @brief Properties
//*/
//
///// Checkbox Property
//inline void Property(const string &label, bool &value) {
//    ImGui::Checkbox(label.c_str(), &value);
//}
//
///// Color Property
//inline void Property(const string &label, float *colors) {
//    ImGui::Columns(2);
//    ImGui::SetColumnWidth(0, 96.0f);
//    ImGui::Text(label.c_str());
//    ImGui::NextColumn();
//    ImGui::ColorEdit4("", colors);
//    ImGui::Columns(1);
//}
//
///// Floating-Point Property
//inline void Property(const string &caption, float &value, float min = 0.0f, float max = 1.0f) {
//    ImGui::SliderFloat(caption.c_str(), &value, min, max);
//}
//
///// State Property
//template <typename ... Args>
//inline void Property(const string &label, const string &format, const Args &...arguments) {
//    ImGui::Columns(2);
//    ImGui::SetColumnWidth(0, 96.0f);
//    ImGui::Text(label.c_str());
//    ImGui::NextColumn();
//    ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, format.c_str(), arguments...);
//    //ImGui::PushStyleColor(ImGuiCol_Text, GetTextColorHighlight());
//    //ImGui::Text(format.c_str(), arguments...);
//    //ImGui::PopStyleColor();
//    ImGui::Columns(1);
//}

}

}
