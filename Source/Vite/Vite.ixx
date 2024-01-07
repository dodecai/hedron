export module Vite;

/// Configuration
import "Vite/Vite.inl";

/// Base
export import Vite.Base;

/// Core
export import Vite.Core;

/// Engine (Systems)
export import Vite.Engine;

/// Tools
export import Vite.Tool;

/// Information
export namespace Hedron::Debug {

/// Display compile-time information
inline void DisplayCompileInformation() {
    Log("\nApp Information\n\t- Caption:\t{}\n\t- Description:\t{}\n\t- Release:\t{}\n\t- Version:\t{}\n",
        "?", //AppCaption,
        "?", //AppDescription,
        "?", //AppRelease,
        "?"  //AppVersion
    );
    Log("\nLibrary Information\n\t- Caption:\t{}\n\t- Description:\t{}\n\t- Release:\t{}\n\t- Version:\t{}\n",
        LibCaption,
        LibDescription,
        LibRelease,
        LibVersion
    );
}

}
