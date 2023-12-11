#include "EventDispatch.h"

namespace app {
    void EventDispatch::dispatch(Event &event) const {
        const auto &handlers = this->eventHandlers[event.type];

        for (auto &handle: handlers) {
            handle(event);

            if (event.handled) {
                break;
            }
        }
    }

    void EventDispatch::subscribe(Event::Type type, EventHandler handler) {
        eventHandlers[type].push_front(handler);
    }

    void EventDispatch::unsubscribe(Event::Type type, EventHandler handler) {
        eventHandlers[type].remove(handler);
    }
}
