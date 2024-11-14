export module Vite.Aurora.Control.Image;

import Vite.Core;
import Vite.Renderer.Texture;
import Vite.Aurora.Control;

export namespace Hedron::UI {

struct Image: public Control {
public:
    Image(const string &id):
        Control(id, ComponentType::Image) {}
    virtual ~Image() = default;

    void Draw() override;

public:
    Reference<Texture> Data {};
};

}
