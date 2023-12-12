#include <iostream>
#include <cstring>

class Worker {
protected:
    char* name;
    int salary;
    Worker* previous, *next;

    static Worker* start;

    Worker(const char* name, const int& salary, bool add = false) : salary(salary), next(nullptr), previous(nullptr) {
        auto len = strlen(name) + 1;
        this->name = new char[len] {};
        strncpy_s(this->name, len, name, len);

        if (add) this->add();
    }
public:
    virtual const char* getName() const {
        return name;
    }

    virtual int getSalary() const {
        return salary;
    }

    virtual const char* getType() const = 0;

    virtual void print() {
        for (auto ptr = Worker::start; ptr != nullptr; ptr = ptr->next) {
            std::cout << ptr->getName() << ' ' << ptr->getSalary() << ' ' << ptr->getType() << '\n';
        }
    }

    void add() {
        if (Worker::start == nullptr) {
            Worker::start = this;
            return;
        }

        for (Worker* worker = Worker::start, *prev = nullptr; worker != nullptr; worker = (prev = worker)->next) {
            if (worker->next == nullptr) {
                worker->next = this;
                worker->previous = prev;
                break;
            }
        }
    }

    virtual ~Worker() {
        if (next != nullptr && previous != nullptr) previous->next = next;
        delete[] name;
    }

    static Worker* show() {
        return start;
    }
};

Worker* Worker::start = nullptr;

class Employee : public Worker {
public:
    Employee(const char* name, const int& salary, bool add = false) : Worker(name, salary, add) {
        std::cout << "Employee(const char* name, const int& salary)\n";
    }

    const char* getType() const override {
        return "Employee";
    }

    ~Employee() override {
        std::cout << "~Employee()\n";
    }
};

class Manager : public Worker {
public:
    Manager(const char* name, const int& salary, bool add = false) : Worker(name, salary, add) {
        std::cout << "Manager(const char* name, const int& salary)\n";
    }

    const char* getType() const override {
        return "Manager";
    }

    ~Manager() override {
        std::cout << "~Manager()\n";
    }
};

class Engineer : public Worker {
public:
    Engineer(const char* name, const int& salary, bool add = false) : Worker(name, salary, add) {
        std::cout << "Engineer(const char* name, const int& salary)\n";
    }

    const char* getType() const override {
        return "Engineer";
    }

    ~Engineer() override {
        std::cout << "~Engineer()\n";
    }
};

int main() {
    auto employee = new Employee("Alice", 1000, true);
    auto manager  = new Manager("Bob", 2000);
    auto engineer = new Engineer("Alex", 3000);

    engineer->add();
    manager->add();

    Worker::show()->print();

    delete engineer;

    Worker::show()->print();

    delete manager;
    delete employee;
}
