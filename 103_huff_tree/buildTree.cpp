#include "node.h"

Node *  buildTree(uint64_t * counts) {
  //WRITE ME!


    priority_queue_t pq;
    for(size_t i=0; i<257; i++) {
        if (counts[i] != 0) {
            pq.push(new Node(i, counts[i]));
        }
    }
    
    while (pq.size() > 1) {
        Node * l = pq.top(); //returns the top item on the PQ
        pq.pop(); //removes the top item of the queue
        Node * r = pq.top(); //return
        pq.pop(); //remove
        Node * node = new Node(l, r);
        pq.push(node);
    }
    return pq.top();



}  
