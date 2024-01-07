export module Vite.Type.Object;

import std;

///
/// @brief Contains classes for managing object behavior and immutability.
/// @detail They can be used as base classes to ensure specific behaviors.
/// @note The classes here are useful for controlling copying, moving, and modification of objects in the application.
///

export namespace Hedron {

///
/// @brief Removes the move constructer/operator from a derived class.
///
class CopyableObject {
protected:
    /// Default
    CopyableObject() = default;
    virtual ~CopyableObject() = default;

public:
    CopyableObject(CopyableObject &&) noexcept = delete;
    CopyableObject &operator=(CopyableObject &&) noexcept = delete;
};

///
/// @brief Removes the copy constructer/operator from derived class.
///
class MoveableObject {
protected:
    /// Default
    MoveableObject() = default;
    virtual ~MoveableObject() = default;

public:
    MoveableObject(const MoveableObject &) = delete;
    MoveableObject &operator=(const MoveableObject &) = delete;
};

///
/// @brief Removes all constructors and the destructor to prevent instantiation and inheritance.
///
class StaticObject {
public:
    /// Default
    StaticObject() = delete;
    virtual ~StaticObject() = delete;
    StaticObject(const StaticObject &) = delete;
    StaticObject(StaticObject &&) noexcept = delete;
    StaticObject &operator=(const StaticObject &) = delete;
    StaticObject &operator=(StaticObject &&) noexcept = delete;
};

///
/// @brief Removes the copy and move constructer/operator from derived class.
///
class SteadyObject {
protected:
    /// Default
    SteadyObject() = default;
    virtual ~SteadyObject() = default;

public:
    SteadyObject(const SteadyObject &) = delete;
    SteadyObject(SteadyObject &&) noexcept = delete;
    SteadyObject &operator=(const SteadyObject &) = delete;
    SteadyObject &operator=(SteadyObject &&) noexcept = delete;
};


///
/// @brief Restricts access to certain methods or properties of objects.
/// @note Left for future use.
///
class AccessControlledObject {
protected:
    /// Default
    AccessControlledObject() = default;
    virtual ~AccessControlledObject() = default;
    
    /// Methods
    void Restricted() {
        if (!mAllowedAccess) throw std::runtime_error("Access not allowed.");
    }

private:
    /// Properties
    bool mAllowedAccess {};
};

///
/// @brief Facilitates object configuration by providing preset options.
/// @note Left for future use.
///
class ConfigurationObject {
protected:
    /// Default
    ConfigurationObject() = default;
    virtual ~ConfigurationObject() = default;
};

///
/// @brief Provides a template for objects that can be serialized and deserialized.
/// @tparam T The data type that represents the serialized form of the object.
/// 
/// @example
/// class ExampleClass : public SerializableObject<string> {
/// public:
///     string Serialize() override {
///         // Implement serialization logic to convert object data to a string
///     }
/// 
///     void Deserialize(const string &data) override {
///         // Implement deserialization logic to restore object data from the string
///     }
/// };
///
template <typename T>
class SerializableObject {
public:
    /// Default
    SerializableObject() = default;
    virtual ~SerializableObject() = default;

    /// Methods
    virtual T Serialize() = 0;
    virtual void Deserialize(const T &data) = 0;
};

///
/// @brief Ensures thread-safe usage of objects through locking mechanisms.
/// 
/// @example
/// ThreadSafeObject::LockGuard lock(*this);
///
class ThreadSafeObject {
protected:
    // Types
    class LockGuard {
    public:
        /// Default
        LockGuard(ThreadSafeObject &object): mObject(object) { mObject.Lock(); }
        ~LockGuard() { mObject.Unlock(); }

    private:
        /// Properties
        ThreadSafeObject &mObject;
    };

protected:
    /// Default
    ThreadSafeObject() = default;
    virtual ~ThreadSafeObject() = default;

    /// Methods
    void Lock() {
        mMutex.lock();
    }
    void Unlock() {
        mMutex.unlock();
    }

private:
    // Properties
    std::mutex mMutex;
};

}
