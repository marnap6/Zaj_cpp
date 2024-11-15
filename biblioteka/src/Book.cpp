#include "Book.h"
#include <iostream>

Book::Book(const std::string& title, const std::string& author, const std::string& publisher, int pages)
        : title(title), author(author), publisher(publisher), pages(pages) {}

void Book::displayInfo() const {
    std::cout << "Book: " << title << ", Author: " << author
              << ", Publisher: " << publisher << ", Pages: " << pages << std::endl;
}
