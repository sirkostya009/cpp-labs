#ifndef OPERATING_SYSTEMS_LABS_WORKER_H
#define OPERATING_SYSTEMS_LABS_WORKER_H

namespace app {
    class Worker {
    protected:
        char *name;
        int salary;

    public:
        Worker(const char *name, const int &salary);

        const char *getName() const;

        int getSalary() const;

        virtual const char *getType() const = 0;

        virtual ~Worker();
    };

    class Employee : public Worker {
    public:
        Employee(const char *name, const int &salary) : Worker(name, salary) {
        }

        const char *getType() const override;
    };

    class Manager : public Worker {
    public:
        Manager(const char *name, const int &salary) : Worker(name, salary) {
        }

        const char *getType() const override;
    };

    class Engineer : public Worker {
    public:
        Engineer(const char *name, const int &salary) : Worker(name, salary) {
        }

        const char *getType() const override;
    };
}

#endif //OPERATING_SYSTEMS_LABS_WORKER_H
