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
                std::cout<<"::"<<nodeList[i].getNumFT();
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
        int nodeGraph::getTotal(int nodeName){//must fix
            node myNode=nodeList[nodeName-1];
            int sum=0;
            for(int i=0; i<myNode.outNodes.size();i++){
                sum = sum + getTotal(myNode.outNodes[i]->getName());
            }
            return sum+myNode.getValue();
        }
        std::vector<int> mft;
        int nodeGraph::findPathsOfFollowingTasks(int nodeName){
        
            node myNode=nodeList[nodeName-1];
            int sum=0;
            for(int i=0; i<myNode.outNodes.size();i++){
                
                sum = sum + findPathsOfFollowingTasks(myNode.outNodes[i]->getName());
                mft.push_back(myNode.outNodes[i]->getName());
                
            }
            return sum+1;
        
        }
         
        int nodeGraph::numberOfFollowingTasks(int taskname){
            
            int k = findPathsOfFollowingTasks(taskname);
            int sum = 1;
            sort( mft.begin(), mft.end() );
            mft.erase( unique( mft.begin(), mft.end() ), mft.end() );
            std::cout<<"\n";
            for (int i=0;i<mft.size();i++){
                sum++;
                std::cout<<mft[i]<<",";
            
            }
            mft.clear();
            return sum;
        }
        
        void nodeGraph::setFollowingTasks(){
        
            for(int i =0; i< nodeList.size();i++){
            
                nodeList[i].setNumFT(numberOfFollowingTasks(i+1));
            
            }
        }