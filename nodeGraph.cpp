#include "nodeGraph.h" 
#include "node.h" 


        nodeGraph::nodeGraph(){
        }
        void nodeGraph::insertNode(int nodeName,int nodeValue){
            node *inputNode=new node(1,"hello");
            nodeList.push_back(*inputNode);
        }
        void nodeGraph::insertEdge(int leftName,int rightName){   
            
//            nodeList[leftName-1].name;
            
        }
         
        