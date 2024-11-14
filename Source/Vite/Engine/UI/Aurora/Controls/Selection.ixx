export module Vite.Aurora.Control.Selection;

import Vite.Core;
import Vite.FontRenderer;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class Selection: public Control {
public:
    Selection(const string &id, string_view text, const vector<string> &options):
        Control(id, ComponentType::Selection),
        Text(text),
        Options(options) {
        Padding = { 8.0f, 8.0f, 8.0f, 8.0f };
        SelectedIndex = 0;
    }
    ~Selection() = default;

    void Draw() override;
    void Update() override {
        if (Font) {
            MinSize = Font->GetSize(Text);
            MinSize.Width += Padding.Left + Padding.Right;
            MinSize.Height += Padding.Top + Padding.Bottom;
            Position.X -= Padding.Left + Offset.X;
            Position.Y -= Padding.Top + Offset.Y;
        }
        if (Options.size() > 0) {
            auto minSize = Size2D {};
            for (auto &&option : Options) {
                auto size = Font->GetSize(option);
                //minSize += size;
            }
            //minSize.Width += Padding.Left + Padding.Right;
            //minSize.Height += Padding.Top + Padding.Bottom;
        }
    }

private:
    void DrawDropdown();

public:
    Font *Font {};
    string Text {};
    vector<string> Options;
    std::function<void()> Click;

private:
    size_t SelectedIndex {};
    bool ShowDropdown = false;
};

}
