export module Vite.Aurora.Control.Seperator;

import Vite.Core;
import Vite.FontRenderer;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class Seperator: public Control {
public:
    Seperator(const string &id):
        Control(id, ComponentType::Seperator) {}
    virtual ~Seperator() = default;

    void Draw() override;
    void Update() override {
        //const float pad = 64.0f;
        //float xMin = std::min(e->p1.x, e->p2.x) - pad;
        //float yMin = std::min(e->p1.y, e->p2.y) - pad;
        //float xMax = std::max(e->p1.x, e->p2.x) + pad;
        //float yMax = std::max(e->p1.y, e->p2.y) + pad;
        //float sx = xMax - xMin;
        //float sy = yMax - yMin;
        // UIRenderer::Line(e->Start, e->Stop, e->Color);
    }
};

}
