#include <iostream>
#include "sequence.h"

int main() {
    int edit_dist = 2;
    std::string motif = "ACGTAG";
    std::string genome_seq = "ACGGATCGGCATCGT";

    Sequence sequence(motif, genome_seq, edit_dist);
    sequence.find_motifs();

    return 0;
}
