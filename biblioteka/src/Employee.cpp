#include "Employee.h"
#include <iostream>

Employee::Employee(const std::string& firstName, const std::string& lastName, const std::string& pesel,
                   const std::string& position, double salary)
        : Person(firstName, lastName, pesel), position(position), salary(salary) {}

void Employee::displayInfo() const {
    std::cout << "Employee: " << firstName << " " << lastName
              << ", PESEL: " << pesel << ", Position: " << position
              << ", Salary: " << salary << std::endl;
}
