#include "node.h" 

   node::node(){
   }
   node::node(int val,int nam){
       weight=val;
       name=nam;
       done=false;
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
   bool node::getDone(){
       return done;
   }
   void node::setDone(bool don){
       done=don;
   }

   void node::insertInputNode(node* n){
       inNodes.push_back(n);
   }
   void node::insertOutputNode(node* n){
       outNodes.push_back(n);
   }