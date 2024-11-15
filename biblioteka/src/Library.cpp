#include "Library.h"
#include <iostream>

void Library::addPerson(const std::shared_ptr<Person>& person) {
    people.push_back(person);
}

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::displayPeople() const {
    for (const auto& person : people) {
        person->displayInfo();
    }
}

void Library::displayBooks() const {
    for (const auto& book : books) {
        book.displayInfo();
    }
}
