#include "StdAfx.h"
#include "node.h"
Node::Node(){
	FibHeapNode::FibHeapNode();
	selected=0;
	visited=0;
}
Node::~Node(){
	
}
void Node::operator =(FibHeapNode& RHS){
	state=RHS.state;
	totalCost=RHS.totalCost;
	column=RHS.column;
	row=RHS.row;
//	for(int i=0;i<8;i++)linkCost[i]=RHS.linkCost[i];
//	prevNode=RHS.prevNode;
}
int Node::operator ==(FibHeapNode& RHS){
	if(column==RHS.column&&row==RHS.row)
		return 1;
	return 0;
}
int Node::operator <(FibHeapNode& RHS){
	 if(totalCost<RHS.totalCost)
		return 1;
     return 0;

}