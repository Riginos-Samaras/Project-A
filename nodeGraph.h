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
         std::vector<node> queue;
    public:  
        nodeGraph();  
        void insertNode(int,int);
        void insertEdge(int,int);
        std::vector<node> getQueue();
        void removeNodeFromQueue(node);
        void printNodes();
        int getTotal(int); 
        int findPathsOfFollowingTasks(int);
        int numberOfFollowingTasks(int);
        void setFollowingTasks();
        void checkAvailable();
        void vectorPrinter(std::vector<node>);
};
#endif	/* NODEGRAPH_H */

