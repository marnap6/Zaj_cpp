#include "Person.h"

Person::Person(const std::string& firstName, const std::string& lastName, const std::string& pesel)
        : firstName(firstName), lastName(lastName), pesel(pesel) {}

std::string Person::getPesel() const {
    return pesel;
}
