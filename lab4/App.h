#ifndef OPERATING_SYSTEMS_LABS_APP_H
#define OPERATING_SYSTEMS_LABS_APP_H

#include <memory>
#include        "Worker.h"
#include          "List.h"
#include "EventDispatch.h"

namespace app {
    class App {
    private:
        App();

    public:
        static App instance;

        List<std::shared_ptr<Worker>>* list;
        EventDispatch* dispatch;

        void run() const;

        ~App();
    };
}

#endif //OPERATING_SYSTEMS_LABS_APP_H
