#include "rosalind.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <unordered_map>


// ------------------- FastaProcessor -------------------
void FastaProcessor::readFasta(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Błąd: Nie można otworzyć pliku " << filename << std::endl;
        return;
    }

    std::string line;
    sequence.clear();
    label.clear();
    nucleotide_count.clear();
    sequences.clear();

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            label = line.substr(1);
            sequences.push_back("");
            continue;
        }
        sequences.back() += line;
        sequence += line;
    }
    file.close();

    for (char nucleotide : sequence) {
        nucleotide_count[nucleotide]++;
    }
}
void FastaProcessor::printNucleotideStats() const {
    if (sequence.empty()) {
        std::cerr << "Brak danych - najpierw wczytaj plik FASTA.\n";
        return;
    }

    int total = sequence.length();
    std::cout << "Nukleotydy:\n";
    for (char nucleotide : {'A', 'C', 'G', 'T'}) {
        int count = nucleotide_count.at(nucleotide);
        double percent = (count * 100.0) / total;
        std::cout << nucleotide << ": " << count << " ("
                  << std::fixed << std::setprecision(2) << percent << "%)\n";
    }
}

std::string FastaProcessor::translateToRNA() const {
    std::string rna_sequence = sequence;
    for (char& nucleotide : rna_sequence) {
        if (nucleotide == 'T') {
            nucleotide = 'U';
        }
    }
    return rna_sequence;
}

std::string FastaProcessor::getComplementaryStrand() const {
    std::string complementary = sequence;
    for (char& nucleotide : complementary) {
        switch (nucleotide) {
            case 'A': nucleotide = 'T'; break;
            case 'T': nucleotide = 'A'; break;
            case 'C': nucleotide = 'G'; break;
            case 'G': nucleotide = 'C'; break;
        }
    }
    std::reverse(complementary.begin(), complementary.end());
    return complementary;
}

double FastaProcessor::calculateGCContent() const {
    if (sequence.empty()) return 0.0;
    int gc_count = nucleotide_count.at('G') + nucleotide_count.at('C');
    return (gc_count * 100.0) / sequence.length();
}

std::vector<int> FastaProcessor::findSubstringPositions(const std::string& subSequence) const {
    std::vector<int> positions;
    size_t pos = sequence.find(subSequence, 0);
    while (pos != std::string::npos) {
        positions.push_back(pos + 1);
        pos = sequence.find(subSequence, pos + 1);
    }
    return positions;
}

// ------------------- ProteinTranslator -------------------
ProteinTranslator::ProteinTranslator() {
    codonTable = {
            {"UUU", 'F'}, {"UUC", 'F'}, {"UUA", 'L'}, {"UUG", 'L'},
            {"UCU", 'S'}, {"UCC", 'S'}, {"UCA", 'S'}, {"UCG", 'S'},
            {"UAU", 'Y'}, {"UAC", 'Y'}, {"UAA", '*'}, {"UAG", '*'},
            {"UGU", 'C'}, {"UGC", 'C'}, {"UGA", '*'}, {"UGG", 'W'},
            {"CUU", 'L'}, {"CUC", 'L'}, {"CUA", 'L'}, {"CUG", 'L'},
            {"CCU", 'P'}, {"CCC", 'P'}, {"CCA", 'P'}, {"CCG", 'P'},
            {"CAU", 'H'}, {"CAC", 'H'}, {"CAA", 'Q'}, {"CAG", 'Q'},
            {"CGU", 'R'}, {"CGC", 'R'}, {"CGA", 'R'}, {"CGG", 'R'},
            {"AUU", 'I'}, {"AUC", 'I'}, {"AUA", 'I'}, {"AUG", 'M'},
            {"ACU", 'T'}, {"ACC", 'T'}, {"ACA", 'T'}, {"ACG", 'T'},
            {"AAU", 'N'}, {"AAC", 'N'}, {"AAA", 'K'}, {"AAG", 'K'},
            {"AGU", 'S'}, {"AGC", 'S'}, {"AGA", 'R'}, {"AGG", 'R'},
            {"GUU", 'V'}, {"GUC", 'V'}, {"GUA", 'V'}, {"GUG", 'V'},
            {"GCU", 'A'}, {"GCC", 'A'}, {"GCA", 'A'}, {"GCG", 'A'},
            {"GAU", 'D'}, {"GAC", 'D'}, {"GAA", 'E'}, {"GAG", 'E'},
            {"GGU", 'G'}, {"GGC", 'G'}, {"GGA", 'G'}, {"GGG", 'G'}
    };
}

std::string ProteinTranslator::translateRNAtoProtein() const {
    std::string rna = translateToRNA();
    std::string protein;

    for (size_t i = 0; i + 2 < rna.length(); i += 3) {
        std::string codon = rna.substr(i, 3);
        auto it = codonTable.find(codon);
        if (it == codonTable.end()) continue;
        if (it->second == '*') break;
        protein += it->second;
    }

    return protein;
}

// ------------------- Hamming Distance -------------------
int HammingDistanceCalculator::calculateHammingDistance(const std::string& otherSequence) const {
    if (sequence.length() != otherSequence.length()) {
        return -1;
    }

    int distance = 0;
    for (size_t i = 0; i < sequence.length(); i++) {
        if (sequence[i] != otherSequence[i]) {
            distance++;
        }
    }
    return distance;
}

// ------------------- Longest Common Substring -------------------
std::vector<std::string> LongestCommonSubstringFinder::findAllLongestCommonSubstrings() const {
    if (sequences.empty()) return {};

    std::string shortest = *std::min_element(sequences.begin(), sequences.end(),
                                             [](const std::string& a, const std::string& b) {
                                                 return a.length() < b.length();
                                             });

    std::vector<std::string> longestSubstrings;
    size_t max_length = 0;

    for (size_t l = shortest.size(); l > 0; --l) {
        for (size_t i = 0; i <= shortest.size() - l; ++i) {
            std::string substr = shortest.substr(i, l);
            bool found_in_all = std::all_of(sequences.begin(), sequences.end(),
                                            [&substr](const std::string& seq) {
                                                return seq.find(substr) != std::string::npos;
                                            });

            if (found_in_all) {
                if (substr.length() > max_length) {
                    longestSubstrings.clear();
                    max_length = substr.length();
                }
                if (substr.length() == max_length) {
                    longestSubstrings.push_back(substr);
                }
            }
        }
        if (!longestSubstrings.empty()) break;
    }
    return longestSubstrings;
}
std::string SplicingProcessor::removeIntronsAndTranslate() {
    std::string exonSequence = sequence;

    for (const std::string& intron : introns) {
        size_t pos = exonSequence.find(intron);
        while (pos != std::string::npos) {
            exonSequence.erase(pos, intron.length());
            pos = exonSequence.find(intron);
        }
    }

    sequence = exonSequence;  // Zapisujemy przetworzoną sekwencję
    return translateRNAtoProtein();
}

void SplicingProcessor::readFastaWithIntrons(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Błąd: Nie można otworzyć pliku " << filename << std::endl;
        return;
    }

    std::string line;
    bool firstSequence = true;
    sequence.clear();
    introns.clear();

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') continue;  // Pomijamy nagłówki FASTA

        if (firstSequence) {
            sequence += line;  // Pierwsza sekwencja to główne DNA
        } else {
            introns.push_back(line);  // Kolejne sekwencje to introny
        }
        firstSequence = false;
    }
    file.close();
}

std::vector<std::string> ORFFinder::findORFs() const {
    std::set<std::string> proteinSet;
    std::vector<std::string> orfProteins;

    std::string dnaStrands[2] = {sequence, getComplementaryStrand()};


    for (const auto& dna : dnaStrands) {
        for (int frame = 0; frame < 3; ++frame) {
            std::string rna = dna.substr(frame);
            rna = translateToRNA();

            for (size_t i = 0; i + 2 < rna.length(); i += 3) {
                if (rna.substr(i, 3) == "AUG") {
                    std::string protein;
                    for (size_t j = i; j + 2 < rna.length(); j += 3) {
                        std::string codon = rna.substr(j, 3);
                        if (codonTable.count(codon) && codonTable.at(codon) == '*') break;
                        protein += getAminoAcid(codon);
                    }
                    if (!protein.empty() && proteinSet.insert(protein).second) {
                        orfProteins.push_back(protein);
                    }
                }
            }
        }
    }
    return orfProteins;
}

bool MutationAnalyzer::isTransition(char base1, char base2) const {
    return (base1 == 'A' && base2 == 'G') || (base1 == 'G' && base2 == 'A') ||
           (base1 == 'C' && base2 == 'T') || (base1 == 'T' && base2 == 'C');
}

double MutationAnalyzer::calculateTransitionTransversionRatio(const std::string& s1, const std::string& s2) const {
    if (s1.length() != s2.length()) {
        std::cerr << "Błąd: Sekwencje muszą mieć taką samą długość." << std::endl;
        return -1.0;
    }

    int transitions = 0, transversions = 0;

    for (size_t i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) {
            if (isTransition(s1[i], s2[i])) {
                transitions++;
            } else {
                transversions++;
            }
        }
    }

    if (transversions == 0 || transitions == 0) {
        std::cerr << "Jedna z mutacji nie występuje, stosunek niezdefiniowany." << std::endl;
        return -1.0;
    }

    return static_cast<double>(transitions) / static_cast<double>(transversions);
}