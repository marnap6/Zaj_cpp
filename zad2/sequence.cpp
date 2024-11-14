#include "sequence.h"
#include <iostream>
#include <string>

Sequence::Sequence(const std::string& motif, const std::string& genome_seq, int edit_dist)
        : motif(motif), genome_seq(genome_seq), edit_dist(edit_dist) {
    motif_len = motif.length();
    genome_len = genome_seq.length();
}

int Sequence::calculate_distance(const std::string& fragm_a, const std::string& fragm_b) const {
    int dist = 0;
    for (int i = 0; i < fragm_a.length(); i++) {
        if (fragm_a[i] != fragm_b[i]) {
            dist++;
        }
    }
    return dist;
}

void Sequence::find_motifs() const {
    for (int i = 0; i <= genome_len - motif_len; i++) {
        std::string genome_substring = genome_seq.substr(i, motif_len);

        int mismatches = calculate_distance(motif, genome_substring);

        if (mismatches <= edit_dist) {
            for (int j = motif_len - edit_dist; j <= motif_len; j++) {
                std::cout << i + 1 << " " << j << std::endl;
            }
        }
    }
}
