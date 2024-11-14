export module Vite.Aurora.Control.Button;

import Vite.Core;
import Vite.FontRenderer;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class Button: public Control {
public:
    Button(const string &id, const string &text):
        Control(id, ComponentType::Button),
        Text(text) {
        Alignment = { 0.5f, 0.5f };
        FocusStyle = FocusStyle::Fill;
        FrameOpacity = 0.5f;
        Padding = { 8.0f, 8.0f, 8.0f, 8.0f };
        Stretch = { 1.0f, 1.0f };
    }
    virtual ~Button() = default;

    void DebugPrint(size_t indent) const override {
        Log("{}{}{} [ Text: '{}' | Position: 'x={}, y={}' | Size '{}x{}' ]\n",
            indent == 0 ? "" : string(indent * 2, ' '),
            indent == 0 ? "" : "◌ ",
            ID,
            Text,
            Position.X, Position.Y,
            Size.Width, Size.Height
        );
    }
    void Draw() override;
    void Update() override {
        if (Font) {
            MinSize = Font->GetSize(Text);
            MinSize.Width += Padding.Left + Padding.Right;
            MinSize.Height += Padding.Top + Padding.Bottom;
            Position.X -= Padding.Left + Offset.X;
            Position.Y -= Padding.Top + Offset.Y;
        }
    }

public:
    string Text {};
    Font *Font {};

    std::function<void()> Click;
};

}
