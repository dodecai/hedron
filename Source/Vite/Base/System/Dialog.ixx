export module Vite.System.Dialog;

import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

class Dialog {
public:
    /// Default
    Dialog() = default;
    virtual ~Dialog() = default;
    static Scope<Dialog> Create(void *window);

    /// Methods
    virtual string OpenFile(string_view title, const vector<string> &filter) const = 0;
    virtual string SaveFile(string_view title, const vector<string> &filter) const = 0;
};

}
