#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

class Sequence {
private:
    std::string genome_seq;
    std::string motif;
    int edit_dist;
    int motif_len;
    int genome_len;

    int calculate_distance(const std::string& fragm_a, const std::string& fragm_b) const;

public:
    Sequence(const std::string& motif, const std::string& genome_seq, int edit_dist);

    void find_motifs() const;
};

#endif
