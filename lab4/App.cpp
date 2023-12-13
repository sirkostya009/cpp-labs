#include "App.h"

#include <iostream>
#include <limits>
#include "handlers.h"

namespace app {
    App::App() : list(new List<std::shared_ptr<Worker>>{
        std::make_shared<Employee>("Alice", 1000),
        std::make_shared<Manager>("Bob", 2000),
        std::make_shared<Engineer>("Jack", 500),
    }), dispatch(new EventDispatch()) {
        using namespace handlers;

        dispatch->subscribe(Event::ADD, handleAddEvent);
        dispatch->subscribe(Event::FILTER, handleFilterEvent);
        dispatch->subscribe(Event::PRINT, handlePrintEvent);
        dispatch->subscribe(Event::DELETE, handleDeleteEvent);
    }

    App App::instance = App();

    void App::run() const {
        char operation;
        Event event;

        while (true) {
            std::cout << '>';
            std::cin >> operation;
            std::getline(std::cin, event.data);

            event.handled = false;

            switch (operation) {
            case 'a':
                event.type = Event::ADD;
                break;
            case 'f':
                event.type = Event::FILTER;
                break;
            case 'p':
                event.type = Event::PRINT;
                break;
            case 'd':
                event.type = Event::DELETE;
                break;
            case 'q':
                return;
            default:
                continue;
            }

            dispatch->dispatch(event);
        }
    }

    App::~App() {
        delete list;
        delete dispatch;
    }
}
