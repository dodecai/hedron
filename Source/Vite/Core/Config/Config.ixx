﻿export module Vite.Config;

import Vite.Base;
import Vite.Bridge.YamlCpp;
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
    /// Default
    Config() = default;
    ~Config() = default;

    ///
    /// Methods
    ///

    // Load a config file
    void Load(const string &file) {
        mConfigFile = file;
        try {
            mConfigData = YAML::LoadFile(mConfigFile);
        } catch (std::exception ex) {
            LogError("Something went wrong while loading Config!");
        }

        try {
            if (mConfigData["App"]) {
                //AppCaption = mConfigData["App"]["Caption"].as<std::string>();
                //AppDescription = mConfigData["App"]["Description"].as<std::string>();
                //AppVersion = mConfigData["App"]["Version"].as<std::string>();
            }

            if (mConfigData["Settings"]["Engine"]) {
                //string delimiter = "x";
                //string resolution = mConfigData["Settings"]["Engine"]["Resolution"].as<std::string>();
                //string tokenW = resolution.substr(0, resolution.find(delimiter));
                //string tokenH = resolution.substr(resolution.find(delimiter) + 1);
                //std::istringstream(tokenH) >> WindowHeight;
                //std::istringstream(tokenW) >> WindowWidth;
            }
        } catch (std::exception ex) {
            std::cout << "Something went wrong!" << "\n";
        }
    }

    // Retrieve a setting as desired type
    // @return The setting value or default value if not found
    template <typename T = string>
    T GetSetting(const string &key, const string &value) const {
        if (mConfigData["Settings"][key][value].IsDefined()) {
            try {
                return mConfigData["Settings"][key][value].as<T>();
            } catch (const YAML::Exception &ex) {
                return T {};
            } catch (...) {
                LogError("Could not deduce the type of '{}:{}'!", key, value);
                return T {};
            }
        } else {
            LogWarning("The requested setting '{}:{}' doesn't exist!", key, value);
        }
        return T {};
    }

private:
    /// Properties
    string mConfigFile {};
    YAML::Node mConfigData;
};

}
