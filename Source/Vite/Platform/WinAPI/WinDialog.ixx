module;

#include "Vite/Base/Bridges/WinAPI.h"

export module Vite.Platform.WinDialog;

import Vite.Core;
import Vite.System.Dialog;

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
    HWND mWindowHandle;
};

}
