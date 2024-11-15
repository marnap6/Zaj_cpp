#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"

class Employee : public Person {
private:
    std::string position;
    double salary;

public:
    Employee(const std::string& firstName, const std::string& lastName, const std::string& pesel,
             const std::string& position, double salary);

    void displayInfo() const override;
};

#endif // EMPLOYEE_H
