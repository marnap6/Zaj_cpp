#ifndef READER_H
#define READER_H

#include "Person.h"

class Reader : public Person {
private:
    int borrowedBooks;

public:
    Reader(const std::string& firstName, const std::string& lastName, const std::string& pesel,
           int borrowedBooks);

    void displayInfo() const override;
};

#endif // READER_H
