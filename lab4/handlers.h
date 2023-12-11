#ifndef OPERATING_SYSTEMS_LABS_HANDLERS_H
#define OPERATING_SYSTEMS_LABS_HANDLERS_H

#include "Event.h"

namespace app::handlers {
    void handleAddEvent(Event &event);

    void handleFilterEvent(Event &event);

    void handlePrintEvent(Event &event);

    void handleDeleteEvent(Event &event);
}

#endif //OPERATING_SYSTEMS_LABS_HANDLERS_H
