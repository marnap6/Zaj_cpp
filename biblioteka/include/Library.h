#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include "Person.h"
#include "Book.h"

class Library {
private:
    std::vector<std::shared_ptr<Person>> people;
    std::vector<Book> books;

public:
    void addPerson(const std::shared_ptr<Person>& person);
    void addBook(const Book& book);
    void displayPeople() const;
    void displayBooks() const;
};

#endif // LIBRARY_H
