#ifndef OPERATING_SYSTEMS_LABS_EVENT_H
#define OPERATING_SYSTEMS_LABS_EVENT_H

#include <string>

namespace app {
    struct Event {
        enum Type {
            ADD,
            FILTER,
            PRINT,
            DELETE,
            UNKNOWN,
            COUNT,
        };

        Type type = UNKNOWN;
        bool handled = false;
        std::string data;
    };
}

#endif //OPERATING_SYSTEMS_LABS_EVENT_H
