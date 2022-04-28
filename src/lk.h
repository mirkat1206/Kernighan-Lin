// lk.h
#ifndef LK_H
#define LK_H

#include "node.h"
#include <fstream>
using namespace std;

class LinKernighan {
public:
    // constructor and destructor
    LinKernighan() {}
    ~LinKernighan(){
        for (int i = 0; i < num_nodes_; ++i)
            delete nodes_[i];
    }

    // get and set
    int GetNumNodes() const { return num_nodes_; }
    int GetNumEdges() const { return num_edges_; }

    // input and output
    void ParseInput(ifstream &fin);
    void PrintBin();
    void PrintEdgeTable();

    // solver
    void Solve();
    void InitDvalue();
    void UpdateDvalue(int a, int b);
    void UnlockNodes();
    void CalculateGains();

private:
    int num_nodes_;
    int num_edges_;
    vector<int> bins_[2];
    vector<Node*> nodes_;
    vector<int> edges_a_, edges_b_;
    vector<vector<int>> edge_table_;
    vector<int> gains_;
    vector<int> swap_;
    vector<int> swap_gains_;
};

#endif
