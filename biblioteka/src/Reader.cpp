#include "Reader.h"
#include <iostream>

Reader::Reader(const std::string& firstName, const std::string& lastName, const std::string& pesel,
               int borrowedBooks)
        : Person(firstName, lastName, pesel), borrowedBooks(borrowedBooks) {}

void Reader::displayInfo() const {
    std::cout << "Reader: " << firstName << " " << lastName
              << ", PESEL: " << pesel << ", Borrowed Books: " << borrowedBooks << std::endl;
}
