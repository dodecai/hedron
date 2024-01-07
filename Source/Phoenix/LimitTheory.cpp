import <Settings.h>;
import <Vite/EntryPoint.h>;

import Phoenix;
import Vite;

namespace Hedron {

///
/// @brief Phoenix Game Engine
/// @note This project is used for research purposes.
///
class App: public Application {
public:
    /// Default
    App(const Settings &settings): Application(settings) {}
    ~App() = default;

    /// Methods
    void Create() {
        Engine_Init(2, 1);
        mLua = Lua_Create();

        char const *entryPoint = "./Script/Main.lua";

        if (!File_Exists(entryPoint)) {
            Directory_Change("../../3rd-Party/LibPHX/assets/");
            if (!File_Exists(entryPoint))
                Fatal("can't find script entrypoint <%s>", entryPoint);
        }

        Lua_SetBool(mLua, "__debug__", false); //DEBUG > 0
        Lua_SetBool(mLua, "__embedded__", true);
        Lua_SetNumber(mLua, "__checklevel__", 0); // CHECK_LEVEL [=0]
        Lua_SetStr(mLua, "__app__", "LTheory");
        Lua_DoFile(mLua, "./Script/Main.lua");
    }
    void Destroy() {
        Lua_Free(mLua);
        Engine_Free();
    }
    void Update(DeltaTime deltaTime) {
        Engine_Update();
    }

private:
    /// Properties
    Lua *mLua = nullptr;
};

// Application Entry-Point
Application *CreateApplication() {
    Settings settings = { "Phoenix", "1280x1024" };
    settings.ExternalLoop = true;
    return new App(settings);
}

}
