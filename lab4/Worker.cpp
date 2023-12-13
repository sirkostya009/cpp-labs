#include "Worker.h"

#include <cstring>

namespace app {
    Worker::Worker(const char *name, const int &salary) : salary(salary) {
        auto len = strlen(name) + 1;
        this->name = new char[len]{};
        strncpy_s(this->name, len, name, len);
    }

    const char* Worker::getName() const {
        return name;
    }

    int Worker::getSalary() const {
        return salary;
    }

    Worker::~Worker() {
        delete[] name;
    }

    const char* Employee::getType() const {
        return "Employee";
    }

    const char* Manager::getType() const {
        return "Manager";
    }

    const char* Engineer::getType() const {
        return "Engineer";
    }
}
