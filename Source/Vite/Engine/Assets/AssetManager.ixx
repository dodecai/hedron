export module Vite.Asset.Manager;

import Vite.Core;
import Vite.Asset;
import Vite.Util.String;

export namespace Hedron {

class AssetManager: public SteadyObject {
    // Types
    using AssetFiles = unordered_map<AssetType, vector<string>>;
    using AssetFolders = unordered_map<AssetType, vector<string>>;
    using AssetMappings = unordered_map<AssetType, vector<string>>;

public:
    // Constructors & Destructors
    AssetManager() {
        mAssetFolders = {
            { AssetType::Font,    { "Fonts" } },
            { AssetType::Image,   { "Icons", "Logos" } },
            { AssetType::Model,   { "Models" } },
            { AssetType::Script,  { "Scripts" } },
            { AssetType::Shader,  { "Shaders" } },
            { AssetType::Sound,   { "Sounds" } },
            { AssetType::Texture, { "Textures" } },
        };
        mAssetMappings = {
            { AssetType::Font,    { "otf", "ttf" } },
            { AssetType::Image,   { "jpg", "png" } },
            { AssetType::Model,   { "obj" } },
            { AssetType::Script,  { "cs", "lua" } },
            { AssetType::Shader,  { "glsl", "vert", "frag", "spriv_v" } },
            { AssetType::Sound,   { "mp3", "ogg", "wav" } },
            { AssetType::Texture, { "jpg", "png" } },
        };

        mThreadPool = CreateScope<ThreadPool>(16);
    };
    ~AssetManager() = default;

    // Methods
    static AssetManager &Instance() {
        static AssetManager instance {};
        return instance;
    }

    // Load assets from the specified root folder.
    void Load(string_view root = "Assets/") {
        if (mAssetFolders.empty()) {
            LogError("The asset folder definitions are empty!");
            return;
        }
        if (mAssetMappings.empty()) {
            LogError("The asset extension mappings are empty!");
            return;
        }

        for (auto &&[type, folders] : mAssetFolders) {
            for (auto &&folder : folders) {
                auto &&extensions = mAssetMappings[type];
                string currentRoot = root.data() + folder + "/";

                if (!Directory::Exists(currentRoot)) continue;

                LogInfo("Loading '{}' assets from '{}' ...", to_string(type), currentRoot);
                auto files = Directory::GetFiles(currentRoot, String::Join(extensions, '|'));
                if (!files.empty()) mAssets[type].insert(mAssets[type].end(), files.begin(), files.end());
            }
        }

        #ifdef _MULTITHREADED_ASSET_LOADING
        /// ToDo: Implement multithreaded asset loading.
        // Every asset type needs a custom loader that the asset manager can use.
        // This way, we can load assets in parallel, and continue with the main thread.
        vector<ThreadResult<void(void)>> results;
        auto &&shaders = mAssets[AssetType::Shader];
        for (auto &&shader : shaders) {
            results.push_back(mThreadPool->Enqueue([=] {
                auto code = File::LoadAsText(shader);
                LogInfo("Loaded shader '{}':\n{}\n", shader, "empty");
            }));
        }

        for (auto &&result : results) {
            result.get();
        }
        auto test = true;
        #endif
    }

    // Reset the asset manager.
    void Reset() {
        mAssets.clear();
    }

    // Resolve an asset by its type and path.
    string Resolve(AssetType type, string_view path) {
        auto &assets = mAssets[type];

        for (auto &asset : assets) {
            if (String::Contains(asset, path)) {
                return asset;
            }
        }
        LogWarning("Could not resolve asset '{}' under '{}'!", to_string(type), path);
        return {};
    }

    vector<uint32> GetAsByteArray(AssetType type, string_view name) {
        if (AssetType::Unknown == type) return {};
        auto data = File::LoadAsBinary(name);
        return data;
    }
    string GetAsString(AssetType type, string_view name) {
        if (AssetType::Unknown == type) return {};
        string data = File::LoadAsString(name);
        return data;
    }

private:
    // Properties
    AssetFiles mAssets;
    AssetFolders mAssetFolders;
    AssetMappings mAssetMappings;
    Scope<ThreadPool> mThreadPool;
};

}
