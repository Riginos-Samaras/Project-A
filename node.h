/* 
 * File:   node.h
 * Author: dimitriosboglou
 *
 * Created on February 10, 2015, 6:35 PM
 */

#ifndef NODE_H
#define	NODE_H

 
#include <vector>
#include <string>
#include <iostream>

#ifdef	__cplusplus
extern "C" {
#endif
class node{

 private:
    int weight;
    bool done;
    int name;  
    int numOfFollowingTasks;
 public:
    std::vector<node*> inNodes; 
    std::vector<node*> outNodes; 
    
    node();
    node(int,int);
    int getValue();
    void setValue(int);
    int getName();
    void setName(int);
    bool getDone();
    void setDone(bool);  
    void setNumFT(int);
    int getNumFT();
    void insertInputNode(node*);
    void insertOutputNode(node*);
};

#ifdef	__cplusplus
}
#endif


#endif	/* NODE_H */

