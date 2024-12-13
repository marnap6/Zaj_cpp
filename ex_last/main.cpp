#include <iostream>
#include "library.h"

using namespace std;

int main() {
    try {
        // Tworzymy obiekt DNA i odczytujemy sekwencję z pliku
        DNA dna;
        dna.readFasta("C:\\Users\\marci\\CLionProjects\\untitled13\\dna_sequence.fasta");

        // Sprawdzamy, czy sekwencja jest poprawna
        if (!dna.validate()) {
            throw runtime_error("Nieprawidłowa sekwencja DNA.");
        }

        cout << "Sekwencja DNA: " << dna.getSeq() << endl;

        // Konwersja DNA na RNA
        RNA rna = dna.toRNA();
        cout << "Sekwencja RNA: " << rna.getSeq() << endl;

        // Konwersja RNA na białko
        Protein protein = rna.toProtein();
        cout << "Sekwencja białka: " << protein.getProtein() << endl;

    } catch (const exception& e) {
        cerr << "Błąd: " << e.what() << endl;
    }
    return 0;
}
