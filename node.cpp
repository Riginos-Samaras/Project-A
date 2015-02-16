#include "node.h" 

   node::node(){
   }
   node::node(int val,int nam){
       weight=val;
       name=nam;
       done=false;
       mftDone=false;
   }
   int node::getValue(){
       return weight;
   }
   void node::setValue(int val){
       weight=val;
   }
   int node::getName(){
       return name;
   }
   void node::setName(int nam){
       name=nam;
   }
    void node::setNumFT(int num){
       numOfFollowingTasks=num;
   }
   bool node::getDone(){
       return done;
   }
   void node::setDone(bool don){
       done=don;
   }
   bool node::getMFTdone(){
       return mftDone;
   }
   void node::setMFTdone(bool don){
       mftDone=don;
   }
   void node::insertInputNode(node* n){
       inNodes.push_back(n);
   }
   void node::insertOutputNode(node* n){
       outNodes.push_back(n);
   }
   
   int node::getNumFT(){
   
       return numOfFollowingTasks;
   
   }
