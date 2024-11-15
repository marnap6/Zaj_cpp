#include <iostream>
#include <memory>
#include "Library.h"
#include "Employee.h"
#include "Reader.h"
#include "Book.h"

int main() {
    Library library;

    library.addPerson(std::make_shared<Employee>("Jan", "Kowalski", "12345678901", "Librarian", 3500.0));
    library.addPerson(std::make_shared<Reader>("Anna", "Nowak", "09876543210", 3));

    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "Scribner", 180));
    library.addBook(Book("1984", "George Orwell", "Secker & Warburg", 328));

    std::cout << "People in the library:\n";
    library.displayPeople();

    std::cout << "\nBooks in the library:\n";
    library.displayBooks();

    return 0;
}
