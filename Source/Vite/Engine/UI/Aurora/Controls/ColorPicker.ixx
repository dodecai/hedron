export module Vite.Aurora.Control.ColorPicker;

import Vite.Core;
import Vite.Renderer.Texture;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class ColorPicker: public Control {
public:
    ColorPicker(const string &id):
        Control(id, ComponentType::ColorPicker) {}
    ~ColorPicker() = default;

    void Draw() override;
};


}
