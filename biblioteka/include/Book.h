#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    std::string publisher;
    int pages;

public:
    Book(const std::string& title, const std::string& author, const std::string& publisher, int pages);
    void displayInfo() const;
};

#endif // BOOK_H
