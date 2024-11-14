#ifndef DNASEQUENCE_H
#define DNASEQUENCE_H

#include <string>

class DNASequence {
private:
    std::string sequence;
    int countA, countC, countG, countT;

    void readSequenceFromFile(const std::string& filename);

public:
    DNASequence(const std::string& filename);

    void countNucleotides();
    void printNucleotideCounts() const;
};

#endif
