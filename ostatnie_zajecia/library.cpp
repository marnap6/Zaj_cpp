#include "library.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>

// Implementacja klasy Seq
Seq::Seq() {}
Seq::Seq(std::string s) : seq(s) {}
Seq::~Seq() {}

void Seq::readFasta(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku.");
    }
    std::string line;
    seq = "";
    while (std::getline(file, line)) {
        if (line[0] != '>') {
            seq += line;
        }
    }
    file.close();
}

bool Seq::validate() {
    for (char c : seq) {
        if (c != 'A' && c != 'T' && c != 'C' && c != 'G') {
            return false;
        }
    }
    return true;
}

int Seq::indexOf(const std::string& s) {
    size_t found = seq.find(s);
    return (found != std::string::npos) ? static_cast<int>(found) : -1;
}

void Seq::replace(const std::string& seq_in, const std::string& seq_out) {
    size_t start_pos = 0;
    while ((start_pos = seq.find(seq_in, start_pos)) != std::string::npos) {
        seq.replace(start_pos, seq_in.length(), seq_out);
        start_pos += seq_out.length();
    }
}

int Seq::count(const std::string& s) {
    int count = 0;
    size_t pos = 0;
    while ((pos = seq.find(s, pos)) != std::string::npos) {
        count++;
        pos += s.length();
    }
    return count;
}

std::string Seq::getSeq() const {
    return seq;
}

// Implementacja klasy DNA
DNA::DNA(std::string s) : Seq(s) {}
DNA::DNA() : Seq() {}

RNA DNA::toRNA() {
    std::string rna_seq = seq;
    for (char& c : rna_seq) {
        if (c == 'T') c = 'U';
    }
    return RNA(rna_seq);
}

// Implementacja klasy RNA
RNA::RNA(std::string s) : Seq(s) {}

DNA RNA::toDNA() {
    std::string dna_seq = seq;
    for (char& c : dna_seq) {
        if (c == 'U') c = 'T';
    }
    return DNA(dna_seq);
}

Protein RNA::toProtein() {
    std::string proteinSeq = "";
    for (size_t i = 0; i + 2 < seq.length(); i += 3) {
        std::string codon = seq.substr(i, 3);
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

// Implementacja klasy Protein
Protein::Protein(std::string seq) : proteinSeq(seq) {}

std::string Protein::getProtein() const {
    return proteinSeq;
}
