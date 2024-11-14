export module Vite.Aurora.Container.Window;

import Vite.Core;
import Vite.FontRenderer;
import Vite.Aurora.Container;

export namespace Hedron::UI {

class Window: public Container {
public:
    Window(const string &id, string_view title = ""):
        Container(id, ComponentType::Window),
        Title(title) {}
    virtual ~Window() = default;

public:
    string Title {};
};

}
