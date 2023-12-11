#include "handlers.h"

#include <regex>
#include <iostream>
#include "App.h"

namespace app::handlers {
    auto numberRegex = std::regex(R"(\d+)");
    auto wordRegex = std::regex(R"([a-zA-Z]+)");

    bool isWorkerType(const std::string& type) {
        return type == "employee" || type == "manager" || type == "intern";
    }

    void handleAddEvent(Event &event) {
        event.handled = true;

        std::string name;
        std::string type;
        int salary;

        std::smatch match;

        if (!std::regex_search(event.data, match, numberRegex)) {
            std::cout << "Missing salary\n";
            return;
        }

        salary = std::stoi(match[0]);

        if (!std::regex_search(event.data, match, wordRegex)) {
            std::cout << "Missing name and worker type\n";
            return;
        }

        int iterations = 0;
        do {
            if (isWorkerType(match[0])) {
                type = match[0];
            } else {
                name = match[0];
            }

            event.data = match.suffix();
            iterations++;
        } while (std::regex_search(event.data, match, wordRegex));

        if (iterations < 2) {
            std::cout << "Missing name or worker type\n";
            return;
        }

        if (type == "employee") {
            App::instance.list->append(std::make_shared<Employee>(name.c_str(), salary));
        } else if (type == "manager") {
            App::instance.list->append(std::make_shared<Manager>(name.c_str(), salary));
        } else if (type == "intern") {
            App::instance.list->append(std::make_shared<Engineer>(name.c_str(), salary));
        }
    }

    void handleFilterEvent(Event &event) {
        event.handled = true;
        std::cout << "Filtered\n";
    }

    void handlePrintEvent(Event &event) {
        App::instance.list->forEach([](const std::shared_ptr<Worker>& worker) {
            std::cout << worker->getType() << ' ' << worker->getName() << ' ' << worker->getSalary() << '\n';
        });
        event.handled = true;
    }

    void handleDeleteEvent(Event &event) {
        event.handled = true;
        std::cout << "Deleted!\n";
    }
}
