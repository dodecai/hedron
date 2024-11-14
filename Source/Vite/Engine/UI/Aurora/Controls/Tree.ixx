export module Vite.Aurora.Control.Tree;

import Vite.Core;
import Vite.Renderer.Texture;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class Tree: public Control {
public:
    Tree(const string &id):
        Control(id, ComponentType::Tree) {}
    ~Tree() = default;

    void Draw() override;

private:
    void DrawTreeNode(const Position2D &position, const string_view &text);

};
}
