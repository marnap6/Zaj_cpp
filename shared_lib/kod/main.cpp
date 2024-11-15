#include "C:\Users\marci\CLionProjects\untitled9\library.h"  // Nagłówek z biblioteki

int main() {
    // Tworzymy obiekt klasy readFile, który używa funkcji z biblioteki
    readFile reader;

    // Wywołanie funkcji z biblioteki, przekazując plik FASTA
    reader.readFasta("C:\\Users\\marci\\CLionProjects\\untitled10\\example.fasta");

    return 0;
}
