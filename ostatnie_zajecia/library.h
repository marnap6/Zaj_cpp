#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

// Klasa Seq
class Seq {
protected:
    std::string seq;

public:
    Seq();
    Seq(std::string s);
    virtual ~Seq();

    void readFasta(const std::string& path);
    bool validate();
    int indexOf(const std::string& s);
    void replace(const std::string& seq_in, const std::string& seq_out);
    int count(const std::string& s);
    std::string getSeq() const;
};

// Klasa DNA dziedzicząca po Seq
class DNA : public Seq {
public:
    DNA(std::string s);
    DNA();
    class RNA toRNA();
};

// Klasa RNA dziedzicząca po Seq
class RNA : public Seq {
public:
    RNA(std::string s);
    class DNA toDNA();
    class Protein toProtein();
};

// Klasa Protein
class Protein {
private:
    std::string proteinSeq;

public:
    Protein(std::string seq);
    std::string getProtein() const;
};

#endif // LIBRARY_H
