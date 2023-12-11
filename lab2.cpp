#include <iostream>
#include <cstring>

class Worker {
protected:
    char* name;
    int salary;

    Worker(const char* name, const int& salary) : salary(salary) {
        auto len = strlen(name) + 1;
        this->name = new char[len] {};
        strncpy_s(this->name, len, name, len);
    }
public:
    virtual const char* getName() const {
        return name;
    }

    virtual int getSalary() const {
        return salary;
    }

    virtual const char* getType() const = 0;

    virtual ~Worker() {
        delete[] name;
    }

    Worker* link{};
};

class Employee : public Worker {
public:
    Employee(const char* name, const int& salary) : Worker(name, salary) {
        std::cout << "Employee(const char* name, const int& salary)\n";
    }

    const char* getType() const override {
        return "Employee";
    }

    ~Employee() {
        std::cout << "~Employee()\n";
    }
};

class Manager : public Worker {
public:
    Manager(const char* name, const int& salary) : Worker(name, salary) {
        std::cout << "Manager(const char* name, const int& salary)\n";
    }

    const char* getType() const override {
        return "Manager";
    }

    ~Manager() {
        std::cout << "~Manager()\n";
    }
};

class Intern : public Worker {
public:
    Intern(const char* name, const int& salary) : Worker(name, salary) {
        std::cout << "Intern(const char* name, const int& salary)\n";
    }

    const char* getType() const override {
        return "Intern";
    }

    ~Intern() {
        std::cout << "~Intern()\n";
    }
};

template <typename T>
class Group {
    T* elements;
    std::size_t size;

    Group(T* elements, const std::size_t& size) : elements(elements), size(size) {
    }
public:
    Group(const std::initializer_list<T>& list) : elements(new T[list.size()]), size(0) {
        for (auto& t : list) {
            elements[size++] = t;
        }
    }

    template <typename R, typename F>
    R reduce(F reducer, R initialValue) const {
        R result = initialValue;

        for (auto& element : *this) {
            result = reducer(result, element);
        }

        return result;
    }

    template <typename F>
    void forEach(F consumer) const {
        for (auto& element : *this) {
            consumer(element);
        }
    }

    template <typename F>
    Group<T> filter(F predicate) {
        auto filtered = new T[size];
        std::size_t i = 0;

        for (auto& element : *this) {
            if (predicate(element)) {
                filtered[i++] = element;
            }
        }

        return Group(filtered, i);
    }

    using const_iterator = const T*;

    const_iterator begin() const {
        return elements;
    }

    const_iterator end() const {
        return elements + size;
    }

    ~Group() {
        std::cout << "~Group()\n";
    }
};

int main() {
    auto alice = Manager("Alice", 3500);
    auto bob = Employee("Bob", 2500);
    auto alex = Employee("Alex", 2000);
    auto vasyl = Intern("Vasyl", 500);

    auto group = Group<Worker*>{ &alice, &bob, &alex, &vasyl };

    alice.link = &bob;
    bob.link = &alex;
    alex.link = &vasyl;

    for (Worker* ptr = &alice; ptr != nullptr; ptr = ptr->link) {
        if (ptr->link == nullptr)
            std::cout << "Last employee is: " << ptr->getType() << ' ' << ptr->getName() << '\n';
    }

    group.filter([](const Worker* worker) {
        return worker->getSalary() > 1000;
    }).forEach([](const Worker* worker) {
        std::cout << worker->getType() << ' ' << worker->getName() << '\n';
    });

    auto sum = group.filter([](const Worker* worker) {
        return typeid(*worker) == typeid(Employee);
    }).reduce([](const int& sum, const Worker* worker) {
        return sum + worker->getSalary();
    }, 0);

    std::cout << "Salary sum of Employees " << sum << '\n';
}
