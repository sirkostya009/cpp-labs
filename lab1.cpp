#include <iostream>
#include <cstring>

class Employee {
    char* name;
    int departmentId;
    int employeeId;

public:
    Employee() : name(new char[1] { '\0' }), departmentId(-1), employeeId(-1) {
        std::cout << "No args constructor called\n";
    }

    Employee(const char* name, const int& departmentId, const int& employeeId) : departmentId(departmentId), employeeId(employeeId) {
        auto len = strlen(name) + 1;
        this->name = new char[len];
        strncpy(this->name, name, len);

        std::cout << "All args constructor called with values " << name << ", " << departmentId << ", " << employeeId << '\n';
    }

    Employee(const Employee& item) : Employee(item.name, item.departmentId, item.employeeId) {
        std::cout << "Copy constructor called with values " << name << ", " << departmentId << ", " << employeeId << '\n';
    }

    ~Employee() {
        delete[] name;

        std::cout << "Destructor called\n";
    }

    // getters
    const char* getName() { return name; }
    int getDepartmentId() { return departmentId; }
    int getEmployeeId() { return employeeId; }

    // setters
    const char* setName(const char* newName) {
        delete[] name;
        auto len = strlen(newName) + 1;
        name = new char[len];
        strncpy(name, newName, len);
        return name;
    }
    int setDepartmentId(const int& newId) { return departmentId = newId; }
    int setEmployeeId(const int& newId) { return employeeId = newId; }

    void print() {
        std::cout << "Employee " << name << ". Department ID: " << departmentId << ". Employee ID: " << employeeId << '\n';
    }
};

int main() {
    auto emptyEmployee = new Employee();
    auto bob = new Employee("Bob", 1, 1);
    auto bobCopy = *bob; // copy constructor call here

    delete bob;

    auto printPtr = &Employee::print;

    (bobCopy.*printPtr)();

    delete emptyEmployee;
    // no need to delete bobCopy as it is not a pointer
}
