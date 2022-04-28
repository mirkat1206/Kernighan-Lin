// main.cpp
#include "lk.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
    ifstream fin;
    if (argc == 2) {
        fin.open(argv[1]);
        if (!fin) {
            cerr << "Cannot open the input file \"" << argv[1] << "\"" << endl;
            exit(1);
        }
    } else {
        cerr << "Usage: ./lk <input file>\n";
        exit(1);
    }    
    LinKernighan lk;
    lk.ParseInput(fin);
    lk.PrintBin();
    // lk.PrintEdgeTable();
    lk.Solve();
    lk.PrintBin();
    return 0;
}
