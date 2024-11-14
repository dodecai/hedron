export module Vite.Aurora.Control.CheckBox;

import Vite.Core;
import Vite.FontRenderer;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class CheckBox: public Control {
public:
    CheckBox(const string &id, string_view text, bool &value):
        Control(id, ComponentType::CheckBox),
        Text(text),
        Value(value) {
        Alignment = { 0.0f, 1.0f };
        FocusStyle = FocusStyle::Underline;
        Padding = { 4.0f, 4.0f, 4.0f, 4.0f };
        Stretch = { 1.0f, 0.0f };

        //Alignment = { 0.5f, 0.5f };
        OutherSize = { 16.0f, 16.0f };
        InnerSize = { 10.0f, 10.0f };
    }
    virtual ~CheckBox() = default;

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
            MinSize.Width += Padding.Left + Padding.Right + 32.0f;
            MinSize.Height += Padding.Top + Padding.Bottom + 4.0f;
            Position.X -= Padding.Left * 2 + Offset.X;
            Position.Y -= Padding.Top + Offset.Y;
        }
    }

public:
    string Text {};
    bool Value { false };
    Font *Font {};

public:
    Hedron::Color InnerColor {};
    Position2D InnerPosition {};
    Size2D InnerSize {};

    Hedron::Color OutherColor {};
    Position2D OutherPosition {};
    Size2D OutherSize {};
};

}
