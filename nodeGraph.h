/* 
 * File:   nodeGraph.h
 * Author: dimitriosboglou
 *
 * Created on February 10, 2015, 8:14 PM
 */

#ifndef NODEGRAPH_H
#define	NODEGRAPH_H

#include "node.h"

class nodeGraph{
    private:
         std::vector<node> nodeList;
    public:  
        nodeGraph();  
        void insertNode(int,int);
        void insertEdge(int,int);
};
#endif	/* NODEGRAPH_H */

