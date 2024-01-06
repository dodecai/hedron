export module Vite.System.Library;

import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Library Interface
/// @todo Finish implementation
///
class Library {
public:
    /// Default
    Library() = default;
    virtual ~Library() = default;

    /// Methods
    virtual bool Load(const string &path) = 0;
    virtual void Unload() = 0;

    /// Accessors
    template <typename T>
    T GetFunction(const string &name) {
        return reinterpret_cast<T>(GetFunctionImpl(name));
    }

protected:
    /// Platform Accessors
    virtual void *GetFunctionImpl(const string &name) = 0;
};

}
