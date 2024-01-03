export module Vite.Config;

import Vite.Base;
import Vite.Logger;


export namespace Hedron {

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
        mConfigFile = file;
    }
    template <typename T = string>
    T GetSetting(const string &key, const string &value) const {
        return T {};
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
