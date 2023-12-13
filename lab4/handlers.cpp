#include <regex>
#include <iostream>
#include "App.h"

namespace app::handlers {
    const auto numberRegex = std::regex(R"(\d+)");
    const auto wordRegex = std::regex(R"([a-zA-Z]+)");

    const char* EmployeeType = "Employee";
    const char* ManagerType = "Manager";
    const char* EngineerType = "Engineer";

    bool isWorkerType(const std::string& type) {
        return type == EmployeeType || type == ManagerType || type == EngineerType;
    }

    void handleAddEvent(Event &event) {
        event.handled = true;

        std::string name, type;
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

        if (type == EmployeeType) {
            App::instance.list->append(std::make_shared<Employee>(name.c_str(), salary));
        } else if (type == ManagerType) {
            App::instance.list->append(std::make_shared<Manager>(name.c_str(), salary));
        } else if (type == EngineerType) {
            App::instance.list->append(std::make_shared<Engineer>(name.c_str(), salary));
        }
    }

    void printWorker(const std::shared_ptr<Worker>& worker) {
        std::cout << worker->getType() << ' ' << worker->getName() << ' ' << worker->getSalary() << '\n';
    }

    auto typeSalaryFilter(const std::string& type, const int* salary) {
        auto validType = isWorkerType(type);

        return [&type, salary, validType](const std::shared_ptr<Worker>& worker) {
            return (!validType || worker->getType() == type) && (salary == nullptr || worker->getSalary() >= *salary);
        };
    }

    std::pair<std::string, int*> getTypeAndSalary(const std::string& data) {
        std::string type;
        int* salary = nullptr;

        std::smatch match;

        if (std::regex_search(data, match, numberRegex)) {
            salary = new int;
            *salary = std::stoi(match[0]);
        }

        if (std::regex_search(data, match, wordRegex)) {
            type = match[0];
        }

        return {type, salary};
    }

    void handleFilterEvent(Event& event) {
        event.handled = true;

        auto [type, salary] = getTypeAndSalary(event.data);

        App::instance.list->filter(typeSalaryFilter(type, salary)).forEach(printWorker);

        delete salary;
    }

    void handlePrintEvent(Event &event) {
        event.handled = true;
        App::instance.list->forEach(printWorker);
    }

    void handleDeleteEvent(Event& event) {
        event.handled = true;

        auto [type, salary] = getTypeAndSalary(event.data);

        auto count = App::instance.list->removeIf(typeSalaryFilter(type, salary));

        std::cout << "Deleted " << count << " workers.\n";
        delete salary;
    }
}
