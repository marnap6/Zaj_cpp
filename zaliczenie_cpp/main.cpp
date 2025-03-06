#include <iostream>
#include "rosalind.h"

int main() {
    std::string fastaFile = "C:\\Users\\marci\\CLionProjects\\zadania_ros\\sequence.fasta";
    std::string fastaFile2 = "C:\\Users\\marci\\CLionProjects\\zadania_ros\\sequences.fasta";
    std::string seq1File = "C:\\Users\\marci\\CLionProjects\\zadania_ros\\seq1.fasta";
    std::string seq2File = "C:\\Users\\marci\\CLionProjects\\zadania_ros\\seq2.fasta";

    // Przetwarzanie DNA
    FastaProcessor fasta;
    fasta.readFasta(fastaFile);

    std::cout << "SEKWENCJA DNA\n" << fasta.getSequence() << "\n";


    std::cout << "\n ZAD1 \nZLICZANIE NUKLEOTYDOW\n";
    fasta.printNucleotideStats();

    std::cout << "\n ZADANIE 2 - TLUMACZENIE NA RNA\nRNA\n" << fasta.translateToRNA() << "\n";

    std::cout << "\n ZADANIE 3 \nNIC KOMPLEMENTARNA\n" << fasta.getComplementaryStrand() << "\n";

    double gcContent = fasta.calculateGCContent();
    std::cout << "\n ZADANIE 4\n" << fasta.getLabel() << "\n" << " GC-content: "
              << gcContent << "%\n";

    // Translacja RNA -> Białko
    ProteinTranslator translator;
    translator.readFasta(fastaFile);
    std::cout << "\n ZADANIE 5 - TLUMACZENIE NA BIALKO\n" << translator.translateRNAtoProtein() << "\n";

    // Znajdowanie podciągu
    std::string subSequence = "ATAT";
    std::vector<int> positions = fasta.findSubstringPositions(subSequence);
    std::cout << "\nZADANIE 6 \nPOZYCJE PODCIAGU \"" << subSequence << "\n";
    if (positions.empty()) {
        std::cout << "Podciąg nie znaleziony.\n";
    } else {
        for (int pos : positions) {
            std::cout << pos << " ";
        }
        std::cout << "\n";
    }

    // Obliczanie odległości Hamminga
    HammingDistanceCalculator seq1, seq2;
    seq1.readFasta(seq1File);
    seq2.readFasta(seq2File);
    int hammingDistance = seq1.calculateHammingDistance(seq2.getSequence());
    if (hammingDistance != -1) {
        std::cout << "\nZADANIE 7 \nODLEGLOSC HAMMINGA\n" << hammingDistance << "\n";
    }

    // Znajdowanie najdłuższego wspólnego podciągu
    LongestCommonSubstringFinder finder;
    finder.readFasta(fastaFile2);
    std::vector<std::string> longestCommonSubstrings = finder.findAllLongestCommonSubstrings();
    std::cout << "\nZADANIE 8 \nNAJDLUZSZY WSPOLNY PODCIAG\n";
    if (longestCommonSubstrings.empty()) {
        std::cout << "Brak wspolnego podciagu.\n";
    } else {
        for (const std::string& substr : longestCommonSubstrings) {
            std::cout << substr << "\n";
        }
    }

    std::string splicingFile = "C:\\Users\\marci\\OneDrive\\Pulpit\\zadania_ros\\splicing.fasta";

    SplicingProcessor splicing;
    splicing.readFastaWithIntrons(splicingFile);

    std::string protein = splicing.removeIntronsAndTranslate();

    std::cout << "\nZADANIE 9 \nBIAlKO PO SPLICINGU\n" << protein << "\n";

    std::string orfFile = "C:\\Users\\marci\\OneDrive\\Pulpit\\zadania_ros\\orf.fasta";

    ORFFinder orfFinder;
    orfFinder.readFasta(orfFile);

    std::vector<std::string> orfs = orfFinder.findORFs();

    std::cout << "\nZADANIE 10 \nOTWARTE RAMKI ODCZYTU (ORF)\n";
    if (orfs.empty()) {
        std::cout << "Brak znalezionych ORF.\n";
    } else {
        for (const std::string& orf : orfs) {
            std::cout << orf << "\n";
        }
    }

    std::string filename = "C:\\Users\\marci\\OneDrive\\Pulpit\\zadania_ros\\mutations.fasta";
    std::cout<< "\nZADANIE 11 - zzzzzzzzzzzzzzzzazazaazzzzzzzzzzztransitions tranversions ratio\n";
    MutationAnalyzer analyzer;
    analyzer.readFasta(filename);

    std::vector<std::string> sequences = analyzer.getSequences();

    if (sequences.size() != 2) {
        std::cerr << "Błąd: Plik FASTA powinien zawierać dokładnie dwie sekwencje, znaleziono: "
                  << sequences.size() << std::endl;
        return 1;
    }

    std::cout << "Pierwsza sekwencja: " << sequences[0] << std::endl;
    std::cout << "Druga sekwencja: " << sequences[1] << std::endl;

    double ratio = analyzer.calculateTransitionTransversionRatio(sequences[0], sequences[1]);

    if (ratio == -1.0) {
        return 1;
    }

    std::cout << "Transitions/Transversions Ratio: " << ratio << std::endl;



    return 0;
}
