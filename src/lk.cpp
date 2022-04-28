// lk.cpp
#include "lk.h"
#include <iostream>
#include <string>
using namespace std;

#define INF 9999999

void LinKernighan::Solve() {
    int la = 5;
    int iter = 0;
    do {
        cout << "-----\titeration " << ++iter << "\t-----" << endl;
        this->InitDvalue();
        this->UnlockNodes();
        // 
        swap_.clear();
        swap_gains_.clear();
        do {
            // compute gains
            this->CalculateGains();
            // find largest gain
            int max_gain = -INF, max_gain_edge = -1;
            for (int i = 0; i < num_edges_; ++i) {
                if (gains_[i] > max_gain) {
                    max_gain = gains_[i];
                    max_gain_edge = i;     
                }
            }
            if (max_gain_edge == -1)    // break while condition
                break;
            cout << "max gain = "<< max_gain <<", "
                 << "by edge ( " << edges_a_[max_gain_edge] << " , " << edges_b_[max_gain_edge] << " )" << endl << endl;
            // mark node a and node b
            nodes_[edges_a_[max_gain_edge]]->lock_ = true;
            nodes_[edges_b_[max_gain_edge]]->lock_ = true;
            // store the gain
            swap_.push_back(max_gain_edge);
            swap_gains_.push_back(max_gain);
            // compute new d-values
            this->UpdateDvalue(edges_a_[max_gain_edge], edges_b_[max_gain_edge]);
        } while (1);
        // find maximum swaps
        int max_sum = swap_gains_[0], temp_sum = swap_gains_[0], max_swap = 0;
        for (int i = 1; i < swap_gains_.size(); ++i) {
            temp_sum += swap_gains_[i];
            if (max_sum < temp_sum) {
                max_sum = temp_sum;
                max_swap = i;
            }
        }
        cout << "max_swap: " << max_swap << " , max_sum: " << max_sum << endl;
        // swaps
        if (max_sum <= 0)    // break while condition
            break;
        for (int i = 0; i <= max_swap; ++i) {
            cout << "swap ( " << edges_a_[swap_[i]] << " , " << edges_b_[swap_[i]] << " )" << endl;
            nodes_[edges_a_[swap_[i]]]->SetBin(1 - nodes_[edges_a_[swap_[i]]]->GetBin());
            nodes_[edges_b_[swap_[i]]]->SetBin(1 - nodes_[edges_b_[swap_[i]]]->GetBin());
        }
        cout << endl;
    }while (1);
    cout << "----- end of iterations -----" << endl << endl;
}

void LinKernighan::CalculateGains() {
    for (int i = 0; i < num_edges_; ++i) {
        if (nodes_[edges_a_[i]]->GetBin() == nodes_[edges_b_[i]]->GetBin() ||
            nodes_[edges_a_[i]]->lock_ == true || nodes_[edges_b_[i]]->lock_ == true) {
            gains_[i] = -INF;
            continue;
        }
        gains_[i] = nodes_[edges_a_[i]]->GetDvalue() + nodes_[edges_b_[i]]->GetDvalue() 
                        - 2 * edge_table_[edges_a_[i]][edges_b_[i]];
    }
    for (int i = 0; i < num_edges_; ++i) {
        if (gains_[i] != -INF) {
            cout << "( " << edges_a_[i] << " , " << edges_b_[i] << " ) "
                 << "\t" << gains_[i] << " " << endl;
        }
    }
    cout << endl;
}

void LinKernighan::UnlockNodes() {
    for (int i = 0; i < num_nodes_; ++i) {
        nodes_[i]->lock_ = false;
    }
}

void LinKernighan::UpdateDvalue(int a, int b) {
    for (int i = 0; i < num_nodes_; ++i) {
        if (nodes_[i]->lock_)
            continue;
        // 
        int delta;
        if (nodes_[i]->GetBin() == nodes_[a]->GetBin())
            delta = 2 * edge_table_[i][a] - 2 * edge_table_[i][b] ;
        else
            delta = 2 * edge_table_[i][b] - 2 * edge_table_[i][a] ;
        nodes_[i]->SetDvalue(nodes_[i]->GetDvalue() + delta );
    }
}

void LinKernighan::InitDvalue() {
    for (int i = 0; i < num_nodes_; ++i) {
        int current_bin = nodes_[i]->GetBin();
        int external_cost = 0, internal_cost = 0;
        for (int j = 0; j < num_nodes_; ++j) {
            if (nodes_[j]->GetBin() != current_bin)
                external_cost += edge_table_[i][j];
            else
                internal_cost += edge_table_[i][j];
        }
        nodes_[i]->SetDvalue(external_cost - internal_cost);
    }
}

void LinKernighan::PrintEdgeTable() {
    cout << "  ";
    for (int i = 0; i < num_nodes_; ++i)
        cout << i << " ";
    cout << endl;
    for (int i = 0; i < num_nodes_; ++i) {
        cout << i << " ";
        for (int j = 0; j < num_nodes_; ++j) {
            cout << edge_table_[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;
}


void LinKernighan::PrintBin() {
    cout << "First Bin" << endl;
    for (int i = 0; i < num_nodes_; ++i) {
        if (nodes_[i]->GetBin() == 0)
            cout << " " << i;
    }
    cout << endl << endl
         << "Second Bin" << endl;  
    for (int i = 0; i < num_nodes_; ++i) {
        if (nodes_[i]->GetBin() == 1)
            cout << " " << i;
    }
    cout << endl << endl;
}

void LinKernighan::ParseInput(ifstream &fin) {
    // number of nodes, node id from 0 ~ n
    fin >> num_nodes_;
    for (int i = 0; i < num_nodes_; ++i) {
        Node* n = new Node;
        n->SetId(i);
        nodes_.push_back(n);
    }
    // initial partition, (# of nodes in 1st partition) <= (# of nodes in 2nd partion)    
    for (int i = 0; i < num_nodes_; ++i) {
        int n;
        fin >> n;
        if (i < num_nodes_ / 2)
            nodes_[n]->SetBin(0);
        else
            nodes_[n]->SetBin(1);
    }
    // number of edges
    fin >> num_edges_;
    // 
    gains_.resize(num_edges_);
    edge_table_.resize(num_nodes_);
    for (int i = 0; i < num_nodes_; ++i) {
        edge_table_[i].resize(num_nodes_, 0);
    }
    // (node id) (node id) (edge weight)
    for (int i = 0; i < num_edges_; ++i) {
        int a, b, w;
        fin >> a >> b >> w;
        edges_a_.push_back(a);
        edges_b_.push_back(b);
        edge_table_[a][b] = w;
        edge_table_[b][a] = w;
    }
}
