export module Vite.Aurora.Control.InputBox;

import Vite.Core;
import Vite.FontRenderer;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class InputBox: public Control {
public:
    InputBox(const string &id, const string &text):
        Control(id, ComponentType::Input),
        Text(text) {}
    ~InputBox() = default;

    void Draw() override;
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
    Font *Font {};
    string Text;
};

}
