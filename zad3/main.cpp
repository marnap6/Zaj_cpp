#include <iostream>
#include "DNASequence.h"

int main() {
    // Specify the filename with the correct path if necessary
    DNASequence dna("C:\\Users\\marci\\CLionProjects\\zadanie 4\\rosalind_dna.txt");

    // Count the nucleotides
    dna.countNucleotides();

    // Output the counts in the required format
    dna.printNucleotideCounts();

    return 0;
}
