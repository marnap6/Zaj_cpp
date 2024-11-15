cmake_minimum_required(VERSION 3.10)
project(untitled11)

set(CMAKE_CXX_STANDARD 17)

# Dodajemy folder include do ścieżki wyszukiwania nagłówków
include_directories(include)

# Dodajemy wszystkie pliki źródłowe do projektu
add_executable(untitled11
        main/main.cpp
        src/Person.cpp
        src/Employee.cpp
        src/Reader.cpp
        src/Book.cpp
        src/Library.cpp
)
