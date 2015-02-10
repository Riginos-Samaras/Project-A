#include "nodeGraph.h" 
#include "node.h" 
#include <iterator>

        nodeGraph::nodeGraph(){
        }
        void nodeGraph::insertNode(int nodeName,int nodeWeight){      
            node *inputNode=new node(nodeWeight, nodeName);
            nodeList.push_back(*inputNode);
        }
        void nodeGraph::insertEdge(int leftName,int rightName){   
            nodeList[leftName-1].insertOutputNode(&nodeList[rightName-1]);   
            nodeList[rightName-1].insertInputNode(&nodeList[leftName-1]);   
        }
        void nodeGraph::printNodes(){   
            std::cout<<"RW::Weight::Name->(Edges)\n-------------------";   
            for( int i= 0; i <nodeList.size(); ++i){
                std::cout<<"\n";   
                std::cout<<this->getTotal(i+1);
                std::cout<<"::"<<nodeList[i].getValue();
                std::cout<<"::"<<nodeList[i].getName();   
                 for( int j= 0; j <nodeList[i].outNodes.size(); ++j){
                     if(j==0)
                         std::cout<<"->(";
                     if(j==nodeList[i].outNodes.size()-1)
                         std::cout<<nodeList[i].outNodes[j]->getName()<<")"; 
                     else
                         std::cout<<nodeList[i].outNodes[j]->getName()<<",";
                 }
            }
        }
        int nodeGraph::getTotal(int nodeName){
            node myNode=nodeList[nodeName-1];
            int sum=0;
            for(int i=0; i<myNode.outNodes.size();i++){
                sum = sum + getTotal(myNode.outNodes[i]->getName());
            }
            return sum+myNode.getValue();
        }
         
      /*
int get_total(node x){
 
int len = x.out_nodes.length;
int sum = 0;
 
for (int i = 0; i < len; ++i)
{
    sum = sum + get_total(x.out_nodes[i]);
 
}
 
    return sum + x.value;
 
}*/   