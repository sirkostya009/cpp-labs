#ifndef OPERATING_SYSTEMS_LABS_EVENTDISPATCH_H
#define OPERATING_SYSTEMS_LABS_EVENTDISPATCH_H

#include <list>
#include "Event.h"

namespace app {
    class EventDispatch {
    public:
        using EventHandler = void (*)(Event &);

        void dispatch(Event &event) const;

        void subscribe(Event::Type type, EventHandler handler);

        void unsubscribe(Event::Type type, EventHandler handler);
    private:
        std::list<EventHandler> eventHandlers[Event::Type::COUNT]{};
    };
}

#endif //OPERATING_SYSTEMS_LABS_EVENTDISPATCH_H
