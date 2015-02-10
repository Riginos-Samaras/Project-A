#include "nodeGraph.h" 
#include "node.h" 
#include <iterator>

        nodeGraph::nodeGraph(){
        }
        void nodeGraph::insertNode(int nodeName,int nodeWeight){      
            node *inputNode=new node(nodeWeight, std::to_string(nodeName));
            nodeList.push_back(*inputNode);
        }
        void nodeGraph::insertEdge(int leftName,int rightName){   
            nodeList[leftName-1].insertOutputNode(&nodeList[rightName-1]);   
            nodeList[rightName-1].insertInputNode(&nodeList[leftName-1]);   
        }
        void nodeGraph::printNodes(){   
            for( int i= 0; i <nodeList.size(); ++i){
                std::cout<<"\n";   
                std::cout<<nodeList[i].getName();   
                 for( int j= 0; j <nodeList[i].outNodes.size(); ++j){
                     std::cout<<"->"<<nodeList[i].outNodes[j]->getName(); 
                 }
            }
        }
         
        