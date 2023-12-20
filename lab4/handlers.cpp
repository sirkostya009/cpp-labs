#include "handlers.h"

#include <algorithm>
#include <iostream>
#include "App.h"

namespace app::handlers {
    const char* EmployeeType = "Employee";
    const char* ManagerType = "Manager";
    const char* EngineerType = "Engineer";

    bool isWorkerType(const std::string& type) {
        return type == EmployeeType || type == ManagerType || type == EngineerType;
    }

    bool isNumber(const std::string& string) {
        return std::all_of(string.begin(), string.end(), [](const char& c){ return std::isdigit(c); });
    }

    void handleAddEvent(Event &event) {
        event.handled = true;

        std::string name, type;
        int salary;

        if (event.data.size() < 3) {
            std::cout << "Missing name, worker type and salary\n";
        }

        for (auto& string : event.data) {
            if (isWorkerType(string)) {
                type = string;
            } else if (isNumber(string)) {
                salary = std::stoi(string);
            } else {
                name = string;
            }
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

    std::pair<std::string, int*> getTypeAndSalary(const std::vector<std::string>& data) {
        std::string type;
        int* salary = nullptr;

        for (auto& string : data) {
            if (isWorkerType(string)) {
                type = string;
            } else if (salary == nullptr && isNumber(string)) {
                salary = new int(std::stoi(string));
            }
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
