#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Klasa Seq
class Seq {
protected:
    string seq;

public:
    Seq() {}
    Seq(string s) : seq(s) {}
    virtual ~Seq() {}

    // Funkcja do odczytu z pliku FASTA
    void readFasta(const string& path) {
        ifstream file(path);
        if (!file.is_open()) {
            throw runtime_error("Nie można otworzyć pliku.");
        }
        string line;
        seq = ""; // Zerujemy sekwencję
        while (getline(file, line)) {
            if (line[0] != '>') {
                seq += line;
            }
        }
        file.close();
    }

    // Walidacja sekwencji (sprawdzamy, czy zawiera tylko 'A', 'T', 'C', 'G')
    bool validate() {
        for (char c : seq) {
            if (c != 'A' && c != 'T' && c != 'C' && c != 'G') {
                return false;
            }
        }
        return true;
    }

    // Znajdowanie indeksu sekwencji w stringu
    int indexOf(const string& s) {
        size_t found = seq.find(s);
        return (found != string::npos) ? static_cast<int>(found) : -1;
    }

    // Funkcja do zamiany sekwencji
    void replace(const string& seq_in, const string& seq_out) {
        size_t start_pos = 0;
        while ((start_pos = seq.find(seq_in, start_pos)) != string::npos) {
            seq.replace(start_pos, seq_in.length(), seq_out);
            start_pos += seq_out.length();
        }
    }

    // Liczenie wystąpień sekwencji
    int count(const string& s) {
        int count = 0;
        size_t pos = 0;
        while ((pos = seq.find(s, pos)) != string::npos) {
            count++;
            pos += s.length();
        }
        return count;
    }

    // Getter dla sekwencji
    string getSeq() const {
        return seq;
    }
};

// Klasa DNA dziedzicząca po Seq
class DNA : public Seq {
public:
    DNA(string s) : Seq(s) {}
    DNA() : Seq() {}

    // Konwersja DNA na RNA (zamiana 'T' na 'U')
    class RNA toRNA();
};

// Klasa RNA dziedzicząca po Seq
class RNA : public Seq {
public:
    RNA(string s) : Seq(s) {}

    // Konwersja RNA na DNA
    DNA toDNA() {
        string dna_seq = seq;
        for (char& c : dna_seq) {
            if (c == 'U') c = 'T';
        }
        return DNA(dna_seq);
    }

    // Konwersja RNA na białko
    class Protein toProtein();
};

// Klasa Protein
class Protein {
private:
    string proteinSeq;

public:
    Protein(string seq) : proteinSeq(seq) {}

    // Zwracamy sekwencję białka
    string getProtein() const {
        return proteinSeq;
    }
};

// Implementacja metody toRNA dla DNA
RNA DNA::toRNA() {
    string rna_seq = seq;
    for (char& c : rna_seq) {
        if (c == 'T') c = 'U';
    }
    return RNA(rna_seq);
}

// Implementacja metody toProtein dla RNA
Protein RNA::toProtein() {
    string proteinSeq = "";
    for (size_t i = 0; i + 2 < seq.length(); i += 3) {
        string codon = seq.substr(i, 3);
        if (codon == "AUG") proteinSeq += "M"; // Start
        else if (codon == "UUU" || codon == "UUC") proteinSeq += "F";
        else if (codon == "UUA" || codon == "UUG") proteinSeq += "L";
        else if (codon == "CUU" || codon == "CUC" || codon == "CUA" || codon == "CUG") proteinSeq += "L";
        else if (codon == "AAA" || codon == "AAG") proteinSeq += "K";
        else if (codon == "GAU" || codon == "GAC") proteinSeq += "D";
        else if (codon == "UAA" || codon == "UAG" || codon == "UGA") break; // Stop
        // Dodaj inne kodony według standardowego kodu genetycznego
    }
    return Protein(proteinSeq);
}

#endif // LIBRARY_H
