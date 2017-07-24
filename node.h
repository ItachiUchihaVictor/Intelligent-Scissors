#include "fibheap.h"
class Node: public FibHeapNode{
public:
	int selected;
	int visited;
    double linkCost[8]; 
    Node *prevNode; 
	virtual void Node::operator =(FibHeapNode& RHS);
	virtual int Node::operator ==(FibHeapNode& RHS);
	virtual int Node::operator <(FibHeapNode& RHS);
	virtual ~Node();
	Node();
};