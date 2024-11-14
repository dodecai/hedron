export module Vite.Aurora.Control;

import Vite.Core;
import Vite.Aurora.Component;

export namespace Hedron::UI {

class Control: public Component {
public:
    Control(const string &id, const ComponentType &type):
        Component(id, type) {}
    virtual ~Control() = default;

    template <typename T, typename... Args> requires std::is_base_of_v<Control, T>
    static Scope<T> Create(const std::string &id, Args&&... args) {
        return CreateScope<T>(id, std::forward<Args>(args)...);
    }

    virtual void DebugPrint(size_t indent) const {
        Log("{}{}{}\n", indent == 0 ? "" : string(indent * 2, ' '), indent == 0 ? "" : "◌ ", ID);
    }

private:
    Position2D CanvasPosition {};
    Size2D CanvasSize {};
};

}
