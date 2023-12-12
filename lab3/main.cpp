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
};

class Employee : public Worker {
public:
    Employee(const char* name, const int& salary) : Worker(name, salary) {
    }

    const char* getType() const override {
        return "Employee";
    }
};

class Manager : public Worker {
public:
    Manager(const char* name, const int& salary) : Worker(name, salary) {
    }

    const char* getType() const override {
        return "Manager";
    }
};

class Engineer : public Worker {
public:
    Engineer(const char* name, const int& salary) : Worker(name, salary) {
    }

    const char* getType() const override {
        return "Engineer";
    }
};

template <typename T>
class List {
public:
    struct Node {
        Node *previous, *next;
        T value;
    };

    List(std::initializer_list<T> list = {}) {
        for (auto& i : list) {
            append(i);
        }
    }

    void append(const T& value) {
        auto node = new Node();
        node->value = value;
        node->previous = tail;
        node->next = nullptr;

        if (tail != nullptr)
            tail->next = node;
        else
            head = node;

        tail = node;
    }

    void prepend(const T& value) {
        auto node = new Node();
        node->value = value;
        node->previous = nullptr;
        node->next = head;

        if (head != nullptr)
            head->previous = node;
        else
            tail = node;

        head = node;
    }

    void pop() {
        if (tail == nullptr)
            return;

        auto node = tail;
        tail = tail->previous;

        if (tail != nullptr)
            tail->next = nullptr;
        else
            head = nullptr;

        delete node;
    }

    void push() {
        if (head == nullptr)
            return;

        auto node = head;
        head = head->next;

        if (head != nullptr)
            head->previous = nullptr;
        else
            tail = nullptr;

        delete node;
    }

    void insert(const T& value, const std::size_t& index) {
        if (index == 0) {
            prepend(value);
            return;
        }

        auto node = head;
        for (std::size_t i = 0; i < index; i++) {
            if (node == nullptr)
                return;

            node = node->next;
        }

        auto newNode = new Node();
        newNode->value = value;
        newNode->previous = node->previous;
        newNode->next = node;

        node->previous->next = newNode;
        node->previous = newNode;
    }

    void remove(const std::size_t& index) {
        if (index == 0) {
            push();
            return;
        }

        auto node = head;
        for (std::size_t i = 0; i < index; i++) {
            if (node == nullptr)
                return;

            node = node->next;
        }

        node->previous->next = node->next;
        node->next->previous = node->previous;

        delete node;
    }

    class Iterator {
        Node* node;
    public:
        Iterator(Node* node) : node(node) {
        }

        Iterator& operator++() {
            node = node->next;
            return *this;
        }

        Iterator& operator--() {
            node = node->previous;
            return *this;
        }

        T& operator*() {
            return node->value;
        }

        bool operator==(const Iterator& other) const {
            return node == other.node;
        }

        bool operator!=(const Iterator& other) const {
            return node != other.node;
        }
    };

    const Iterator begin() const {
        return Iterator(head);
    }

    const Iterator end() const {
        return Iterator(nullptr);
    }

    template <typename P>
    List<T> filter(P predicate) {
        auto list = List<T>();

        for (auto& value : *this) {
            if (predicate(value)) {
                list.append(value);
            }
        }

        return list;
    }

    template <class R, typename F>
    R reduce(F reducer, R initialValue) const {
        R result = initialValue;

        for (auto& value : *this) {
            result = reducer(result, value);
        }

        return result;
    }

    template <typename F>
    void forEach(F consumer) const {
        for (auto& value : *this) {
            consumer(value);
        }
    }

    ~List() {
        for (auto node = head; node != nullptr;) {
            auto next = node->next;
            delete node;
            node = next;
        }
    }
private:
    Node *head{}, *tail{};
};

auto main() -> int {
    char input;
    size_t hash;

    start:
    std::cout << "Enter type [M/E/e]: ";
    std::cin >> input;

    switch (input) {
        case 'M':
            hash = typeid(Manager).hash_code();
            break;
        case 'E':
            hash = typeid(Employee).hash_code();
            break;
        case 'e':
            hash = typeid(Engineer).hash_code();
            break;
        default:
            std::cout << "Unknown char\n";
            goto start;
    }

    auto bob = Manager("Bob", 2000);
    auto alice = Employee("Alice", 5000);
    auto alex = Engineer("Alex", 1000);
    auto john = Employee("John", 3000);
    auto jack = Engineer("Jack", 1500);
    auto jessica = Employee("Jessica", 4000);

    auto workers = List<Worker*>{ &bob, &alice, &alex, &john, &jack, &jessica };

    workers.filter([&hash](auto worker) {
        return typeid(*worker).hash_code() == hash;
    }).forEach([](auto worker) {
        std::cout << worker->getType() << ' ' << worker->getName() << '\n';
    });

    auto sum = workers.reduce([](auto sum, auto worker) {
        return sum + worker->getSalary();
    }, 0);

    std::cout << "Salary sum: " << sum << '\n';
}
