#include "nodeGraph.h" 
#include "node.h" 
#include <iterator>
using std::cout;
using std::endl;

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
                
                //cout<<this->getTotal(i+1); //when big inputdata creates problem
               std::cout<<nodeList[i].getRPW();
               std::cout<<"::"<<nodeList[i].getDone();
                //cout<<"::"<<nodeList[i].getValue();
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

        void nodeGraph::setFollowingTasks(){
        
            for(int i =0; i< nodeList.size();i++){
                
                if(nodeList[i].inNodes.size()==0){
                    
                    MFT(nodeList[i].getName());
                
                    
                }
            
            }
        }
        
        void nodeGraph::initDone(){
        
           for(int i =0; i< nodeList.size();i++){
                
                nodeList[i].setDone(false);

            }       
        }
        
        
        
        
        std::set<node*> nodeGraph::MFT(int nodeID){
           
                std::set<node*> sum;
                node* myNode = &nodeList[nodeID-1];
                int tempFT=0;
                int tempRPG=0;
                for (int i = 0; i<myNode->outNodes.size();i++){
                    if(myNode->outNodes[i]->getMFTdone()){
                        tempRPG+=myNode->outNodes[i]->getRPW();
                        
                        tempFT+=myNode->outNodes[i]->getNumFT()+1;
                        continue;}
                    std::set<node*> tempSum;
                    tempSum = MFT(myNode->outNodes[i]->getName());
                    sum.insert(tempSum.begin(),tempSum.end());

                }
        myNode->setMFTdone(true);
        myNode->setNumFT(sum.size()+tempFT);
        
        int total_sum_RPW=0;
        for (std::set<node*>::iterator i = sum.begin(); i != sum.end(); i++) {
  
            
            node* nd = *i;
            total_sum_RPW+=nd->getValue();
            
        }
        myNode->setRPW(total_sum_RPW+myNode->getValue()+tempRPG);
        
        sum.insert(myNode);
        return sum;
        }
        
        void nodeGraph::checkAvailable(){
           
            std::vector<node *> q;
            for(int i=0; i<nodeList.size();i++){
                 
                int check = 1;
                if(!nodeList[i].getDone()){
                    for(int k=0; k<nodeList[i].inNodes.size();k++){
                        
                        if(!nodeList[i].inNodes[k]->getDone()){
                            check=0;
                        }

                    }

                    if(check){ 
                        q.push_back(&nodeList[i]);
                    }
                }
            }
        
            queue = q;
        }
        
        void nodeGraph::vectorPrinter(std::vector<node *> vec){
            std::cout<<std::endl;
            
            for(int i=0; i<vec.size();i++){
                if(i==(vec.size()-1))
                    std::cout<<vec[i]->getName()<<":"<<vec[i]->getDone()<<std::endl;
                else
                    std::cout<<vec[i]->getName()<<":"<<vec[i]->getDone()<<"->";
                
            }
        
        }
        void nodeGraph::vectorNodeListPrinter(std::vector<node > vec){
            std::cout<<std::endl;
            for(int i=0; i<vec.size();i++){
                if(i==(vec.size()-1))
                    std::cout<<vec[i].getName()<<":"<<vec[i].getDone()<<std::endl;
                else
                    std::cout<<vec[i].getName()<<":"<<vec[i].getDone()<<"->";
                
            }
        
        }
        
        
        
        std::vector<node *> nodeGraph::getQueue(){
            checkAvailable();
            return queue;
        
        }   
        
        std::vector<node > nodeGraph::getNodeList(){
           
            return nodeList;
        
        }
        
        void nodeGraph::removeNodeFromQueue(node* nd){
        
            for(int i = 0; i < queue.size();i++){
                
                if(queue[i]->getName()==nd->getName()){
                    
                    queue[i]->setDone(true);
                   // queue.erase(queue.begin()+i);
                }
            }
        }
        
        void nodeGraph::printNodesTemp(){   
            std::cout<<"YOYO";   
            for( int i= 0; i <nodeList.size(); ++i){
                std::cout<<"\n";   
                std::cout<<"::"<<nodeList[i].getName();
               
            }
        }