export module Vite.Aurora.Control.Label;

import Vite.Core;
import Vite.FontRenderer;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class Label: public Control {
public:
    Label(const string &id, string_view text):
        Control(id, ComponentType::Label),
        Text(text) {
        Alignment = { 0.0f, 1.0f };
        Padding = { 2.0f, 1.0f, 2.0f, 1.0f };
        Interactive = false;
        //Stretch = { 1.0f, 1.0f };
    }
    virtual ~Label() = default;

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
            auto test = Font->GetSizeMsdf(Text);
            MinSize.Width += Padding.Left + Padding.Right;
            MinSize.Height += Padding.Top + Padding.Bottom;
            Position.X -= Padding.Left + Offset.X;
            Position.Y -= Padding.Top + Offset.Y;
        }
    }

public:
    string Text {};
    Font *Font {};
};

}
