export module Vite.Aurora.Control.Cursor;

import Vite.Core;
import Vite.Renderer.Texture;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class Cursor: public Control {
public:
    Cursor(const string &id):
        Control(id, ComponentType::Cursor) {}
    virtual ~Cursor() = default;

    Texture *Data {};
    bool Outline {};
};

}
