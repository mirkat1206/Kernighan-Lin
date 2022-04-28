// node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
using namespace std;

class Node {
public:
    // constructor and destructor
    Node(){};
    ~Node(){};

    // get and set
    int GetId()     const { return id_; }
    int GetBin()    const { return bin_; }
    int GetDvalue() const { return dvalue_; }
    void SetId(int nconst ) { id_ = n; }
    void SetBin(int n)      { bin_ = n; }
    void SetDvalue(int n)   { dvalue_ = n; }
    
    // 
    bool lock_;
    
private:
    int id_;
    int bin_;   // 0 or 1
    int dvalue_;
};

#endif
