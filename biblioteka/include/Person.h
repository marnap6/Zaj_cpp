#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string firstName;
    std::string lastName;
    std::string pesel;

public:
    Person(const std::string& firstName, const std::string& lastName, const std::string& pesel);
    virtual ~Person() = default;

    std::string getPesel() const;
    virtual void displayInfo() const = 0; // Pure virtual method
};

#endif // PERSON_H
