#ifndef NODE_H_
#define NODE_H_

struct Node{
    int rank;
    int marked;
    char * name;
    Node * predecessor;
};


#endif
