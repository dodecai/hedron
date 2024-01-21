export module Vite.Event;

export import Vite.Event.Data;
import Vite.Event.Emitter;

export namespace Hedron {

///
/// @brief Event Handler Interface
///
class EventHandler: public EventEmitter {
public:
    /// Default
    EventHandler() = default;
    virtual ~EventHandler() = default;
    static Scope<EventHandler> Create(void *window);

    /// Events
    virtual bool Callback(void *event) = 0;
    virtual void Update() = 0;

protected:
    /// Properties
    Position2D mMouseDeltaPosition {};
    Position2D mMouseLastPosition {};
    Position2D mMousePosition {};
    Position2D mMouseDeltaWheel {};
    Position2D mMouseLastDeltaWheel {};
};

}
