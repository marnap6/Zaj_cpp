#include "DNASequence.h"
#include <fstream>
#include <iostream>

DNASequence::DNASequence(const std::string& filename) : countA(0), countC(0), countG(0), countT(0) {
    readSequenceFromFile(filename);
}

void DNASequence::readSequenceFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::getline(file, sequence);
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void DNASequence::countNucleotides() {
    for (char nucleotide : sequence) {
        switch (nucleotide) {
            case 'A': countA++; break;
            case 'C': countC++; break;
            case 'G': countG++; break;
            case 'T': countT++; break;
            default: break; // Ignore unexpected characters
        }
    }
}

void DNASequence::printNucleotideCounts() const {
    std::cout << countA << " " << countC << " " << countG << " " << countT << std::endl;
}
