#include "library.h"
#include <iostream>
#include <exception>

int main() {
    try {
        // Tworzymy obiekt DNA i odczytujemy sekwencję z pliku
        DNA dna;
        dna.readFasta("C:\\Users\\marci\\CLionProjects\\untitled13\\dna_sequence.fasta");

        // Sprawdzamy, czy sekwencja jest poprawna
        if (!dna.validate()) {
            throw std::runtime_error("Nieprawidłowa sekwencja DNA.");
        }

        std::cout << "Sekwencja DNA: " << dna.getSeq() << std::endl;

        // Konwersja DNA na RNA
        RNA rna = dna.toRNA();
        std::cout << "Sekwencja RNA: " << rna.getSeq() << std::endl;

        // Konwersja RNA na białko
        Protein protein = rna.toProtein();
        std::cout << "Sekwencja białka: " << protein.getProtein() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }

    return 0;
}
