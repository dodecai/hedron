export module Vite.Core.Config;

import Vite.Core.Standard;
//import Vite.Logger;


export namespace Vite {

///
/// @brief Configuration
/// @note ToDo: Instead of fixed properties, we want tu use the multimap directly
/// 
/// @example
/// Scope<Config> config = CreateScope<Config>();
/// config->Load("Data/Config.yml");
/// auto setting = config->GetSetting<string>("key", "value");
///
class Config {
public:
    Config() = default;
    ~Config() = default;

    void Load(const string &file) {
    }

private:
    string mConfigFile {};
    //YAML::Node mConfigData;

    string AppCaption {};
    string AppDescription {};
    string AppVersion {};

    size_t WindowHeight {};
    size_t WindowWidth {};
};

}
