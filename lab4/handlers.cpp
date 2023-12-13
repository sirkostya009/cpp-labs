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


    void printWorker(const std::shared_ptr<Worker>& worker) {
        std::cout << worker->getType() << ' ' << worker->getName() << ' ' << worker->getSalary() << '\n';
    }

    void handleFilterEvent(Event& event) {
        event.handled = true;

        std::string type;
        int* salary = nullptr;

        auto validType = isWorkerType(type);

        List<std::shared_ptr<Worker>> filtered;

        if (salary != nullptr && validType) {
            filtered = App::instance.list->filter([&type, &salary](const std::shared_ptr<Worker>& worker) {
                return worker->getType() == type && worker->getSalary() >= *salary;
                });
        }
        else if (salary != nullptr) {
            filtered = App::instance.list->filter([&salary](const std::shared_ptr<Worker>& worker) {
                return worker->getSalary() >= *salary;
                });
        }
        else if (validType) {
            filtered = App::instance.list->filter([&type](const std::shared_ptr<Worker>& worker) {
                return worker->getType() == type;
                });
        }

        filtered.forEach(printWorker);

        delete salary;
    }

    void handlePrintEvent(Event &event) {
        App::instance.list->forEach([](const std::shared_ptr<Worker>& worker) {
            std::cout << worker->getType() << ' ' << worker->getName() << ' ' << worker->getSalary() << '\n';
        });
        event.handled = true;
    }

    void handleDeleteFilteredEvent(Event& event) {
        event.handled = true;

        std::string type;
        int salary = 0;

        auto validType = isWorkerType(type);
        if (std::regex_search(event.data, numberRegex)) {
            salary = std::stoi(event.data);
        }

        auto filtered = App::instance.list->filter([&type, &salary, &validType](const std::shared_ptr<Worker>& worker) {
            return (!validType || worker->getType() == type) && (salary == 0 || worker->getSalary() >= salary);
            });

        filtered.forEach([](const std::shared_ptr<Worker>& worker) {
            App::instance.list->removeWorker(worker);
            delete worker.get();
            });

        std::cout << "Deleted filtered workers.\n";
    }

}
