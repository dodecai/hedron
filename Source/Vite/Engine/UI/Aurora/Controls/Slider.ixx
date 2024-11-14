export module Vite.Aurora.Control.Slider;

import Vite.Core;
import Vite.FontRenderer;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class Slider: public Control {
public:
    Slider(const string &id, float value, float min, float max):
        Control(id, ComponentType::Slider),
        Value(value),
        MinValue(min),
        MaxValue(max) {
        Alignment = { 0.5f, 0.5f };
        Color = { 0.5f, 0.5f, 0.5f, 1.0f };
        FocusStyle = FocusStyle::Scroll;
        MinSize = { 200.0f, 24.0f };
        Stretch = { 1.0f, 0.0f };
    }
    virtual ~Slider() = default;

    void DebugPrint(size_t indent) const override {
        Log("{}{}{} [ Text: '{}' | Position: 'x={}, y={}' | Size '{}x{}' ]\n",
            indent == 0 ? "" : string(indent * 2, ' '),
            indent == 0 ? "" : "◌ ",
            ID,
            Value,
            Position.X, Position.Y,
            Size.Width, Size.Height
        );
    }
    void Draw() override;
    void Update() override {

    }

public:
    float Value {};
    float MinValue {};
    float MaxValue {};
    float HandleWidth { 6.0f };
    float DragOffset {};
};


}
