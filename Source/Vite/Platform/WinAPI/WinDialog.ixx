export module Vite.Platform.WinDialog;

import Vite.Bridge.WinAPI;
import Vite.Core;
import Vite.System.Dialog;

using namespace WinAPI;

export namespace Hedron {

class WinDialog: public Dialog {
public:
    /// Default
    WinDialog(void *window);
    virtual ~WinDialog();

    /// Methods
    string OpenFile(string_view title = "", const vector<string> &filter = { "All Files (*.*)", "*.*" }) const;
    string SaveFile(string_view title = "", const vector<string> &filter = { "All Files (*.*)", "*.*" }) const;
    
private:
    /// Properties
    WindowHandle mWindowHandle;
};

}
