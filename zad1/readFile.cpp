#include "readFile.h"
#include <iostream>
#include <fstream>

using namespace std;

void readFile::readFasta(const string& name_file) {
    ifstream file(name_file);
    if (!file.is_open()) {
        cout << "Nie można otworzyć pliku: " << name_file << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}
//
// Created by marci on 04.10.2024.
//
