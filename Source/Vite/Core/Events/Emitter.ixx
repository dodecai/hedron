module;

//#include <entt/entt.hpp>

export module Vite.Event.Emitter;

//import Vite.Bridge.EnTT;
import Vite.Base;

///
/// @brief Event Emitter
/// @base https://github.com/skypjack/entt/blob/master/src/entt/signal/emitter.hpp
///

export namespace Hedron {

#ifdef DISABLED_CODE_FOR_NOW
///
/// @brief Event Emitter
/// @warn To create an emitter type, derived classes must inherit from the base.
/// 
/// @note Handlers for the different events are created internally on the fly. It's not required to specify
/// in advance the full list of accepted events. Moreover, whenever an event is published, an emitter also
/// passes a reference to itself to its listeners.
/// 
/// @example
/// struct MyEmitter: Emitter<MyEmitter> {
///     ...
/// }
///
template<typename Derived, typename Allocator>
class Emitter {
    /// Types
    using key_type = entt::id_type;
    using mapped_type = std::function<void(void *)>;

    using alloc_traits = std::allocator_traits<Allocator>;
    using container_allocator = typename alloc_traits::template rebind_alloc<std::pair<const key_type, mapped_type>>;
    using container_type = entt::dense_map<key_type, mapped_type, entt::identity, std::equal_to<key_type>, container_allocator>;

public:
    using allocator_type = Allocator;   // Allocator type. 
    using size_type = std::size_t;      // Unsigned integer type. 

    /// Default
    Emitter(): Emitter { allocator_type{} } {}
    explicit Emitter(const allocator_type &allocator):
        handlers { allocator, allocator } {
    }
    Emitter(Emitter &&other) noexcept: handlers { std::move(other.handlers) } {}
    Emitter(Emitter &&other, const allocator_type &allocator) noexcept: handlers { container_type { std::move(other.handlers.first()), allocator }, allocator } {
        ENTT_ASSERT(alloc_traits::is_always_equal::value || handlers.second() == other.handlers.second(), "Copying an emitter is not allowed");
    }
    virtual ~Emitter() noexcept {
        static_assert(std::is_base_of_v<Emitter<Derived, Allocator>, Derived>, "Invalid emitter type!");
    }

    /// Operators
    Emitter &operator=(Emitter &&other) noexcept {
        ENTT_ASSERT(alloc_traits::is_always_equal::value || handlers.second() == other.handlers.second(), "Copying an emitter is not allowed");

        handlers = std::move(other.handlers);
        return *this;
    }

    /// Methods
    // Disconnects all the listeners.
    void Clear() noexcept {
        handlers.first().clear();
    }

    // Checks if there are listeners registered for the specific event.
    template<typename Type>
    [[nodiscard]] bool Contains() const {
        return handlers.first().contains(entt::type_hash<std::remove_cv_t<std::remove_reference_t<Type>>>::value());
    }

    // Checks if there are listeners registered with the event emitter.
    [[nodiscard]] bool Empty() const noexcept {
        return handlers.first().empty();
    }

    // Disconnects the listener of specified event type from the event emitter.
    template<typename T>
    void Erase() {
        handlers.first().erase(entt::type_hash<std::remove_cv_t<std::remove_reference_t<T>>>::value());
    }

    // Publishes a given event type instance with specified event type to trigger.
    template<typename T>
    void Publish(T &&value) {
        if (const auto id = entt::type_id<T>().hash(); handlers.first().contains(id)) {
            handlers.first()[id](&value);
        }
    }

    // Registers a listener with the event emitter with the specified event type to which to connect the listener.
    template<typename T>
    void Register(std::function<void(T &, Derived &)> func) {
        handlers.first().insert_or_assign(entt::type_id<T>().hash(), [func = std::move(func), this](void *value) {
            func(*static_cast<T *>(value), static_cast<Derived &>(*this));
        });
    }

    // Exchanges the contents with those of a given emitter.
    void Swap(Emitter &other) {
        std::swap(handlers, other.handlers);
    }

    // Returns the associated allocator.
    [[nodiscard]] constexpr allocator_type get_allocator() const noexcept {
        return handlers.second();
    }

private:
    /// Properties
    entt::compressed_pair<container_type, allocator_type> handlers;
};
#endif

///
/// @brief Simple Event Emitter
/// @note There are a lot of bugs around C++20 modules in msvc so to keep it rolling we are using this for now.
///
class EventEmitter {
public:
    /// Methods
    template<typename EventType>
    void Register(std::function<void(const EventType &)> handler) {
        auto &handlers = eventHandlers[typeid(EventType)];
        handlers.push_back([handler = std::move(handler)](const void *event) {
            handler(*static_cast<const EventType *>(event));
        });
    }

    template<typename EventType>
    void Publish(const EventType &event) {
        auto it = eventHandlers.find(typeid(EventType));
        if (it != eventHandlers.end()) {
            for (auto &handler : it->second) {
                handler(&event);
            }
        }
    }

private:
    /// Properties
    unordered_map<std::type_index, vector<function<void(const void *)>>> eventHandlers;
};

}
