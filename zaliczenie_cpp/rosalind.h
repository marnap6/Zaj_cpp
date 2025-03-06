#ifndef ROSALIND_H
#define ROSALIND_H

#include <string>
#include <unordered_map>
#include <vector>
#include <set>

class FastaProcessor {
protected:
    std::string sequence;
    std::string label;
    std::unordered_map<char, int> nucleotide_count;
    std::vector<std::string> sequences;

public:
    FastaProcessor() = default;
    void readFasta(const std::string& filename);
    void printSequence() const;
    void printNucleotideStats() const;
    std::string translateToRNA() const;
    std::string getComplementaryStrand() const;
    double calculateGCContent() const;
    std::string getLabel() const { return label; }
    std::string getSequence() const { return sequence; }
    std::vector<int> findSubstringPositions(const std::string& subSequence) const;
    const std::vector<std::string>& getSequences() const { return sequences; }
};

// Klasa dziedzicząca do tłumaczenia RNA -> Białko
class ProteinTranslator : public FastaProcessor {
public:
    std::unordered_map<std::string, char> codonTable;

public:
    ProteinTranslator();
    std::string translateRNAtoProtein() const;
};

class HammingDistanceCalculator : public FastaProcessor {
public:
    int calculateHammingDistance(const std::string& otherSequence) const;
};

class LongestCommonSubstringFinder : public FastaProcessor {
public:
    std::vector<std::string> findAllLongestCommonSubstrings() const;
};

class SplicingProcessor : public ProteinTranslator {
public:
    void readFastaWithIntrons(const std::string& filename);
    std::string removeIntronsAndTranslate();
private:
    std::vector<std::string> introns;
};

class ORFFinder : public ProteinTranslator {
public:
    std::vector<std::string> findORFs() const;
    char getAminoAcid(const std::string& codon) const {
        auto it = codonTable.find(codon);
        return (it != codonTable.end()) ? it->second : '?'; // '?' dla nieznanych kodonów
    }
};

class MutationAnalyzer : public FastaProcessor {
public:
    double calculateTransitionTransversionRatio(const std::string& s1, const std::string& s2) const;
private:
    bool isTransition(char base1, char base2) const;
};


#endif // ROSALIND_H
