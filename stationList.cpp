#include "stationList.h"
using std::cout;
using std::endl;
stationList::stationList(){}

void stationList::insertStation(){

    station *st = new station(cycleTime);
    stations.push_back(*st);
    
}

void stationList::pushTaskToStation(node *nd){

    if(stations.empty())
        insertStation();
    
    if(stations.back().canInsert(nd))
    {
       
        stations.back().insertTask(nd);
       x.removeNodeFromQueue(nd);
    }
    else{
        
       
        std::vector<node *> vec = x.getQueue();
        bool openNewStation = true;
        for(int i=0; i<vec.size(); i ++)
        {
            if(stations.back().canInsert(vec[i])){
             openNewStation = false;
             stations.back().insertTask(vec[i]);
             x.removeNodeFromQueue(vec[i]);
             break;
            
            }
       
        
        }
        
        if(openNewStation){
            insertStation();
            pushTaskToStation(nd);
        }
    
    }


}
 void stationList::printStations(){
     for(int i=0; i<stations.size();i++){
         cout<<i<<":";
         stations[i].printTasks();
     }
 }
    

    void stationList::setPolicy(std::string policyName){
        
        if (policyName == "LTT") policy=LTT;
        if (policyName == "STT") policy= STT;
        if (policyName == "MFT") policy= MFT;
        if (policyName == "LNFT") policy= LNFT;
        if (policyName == "RPW") policy= RPW;
        if (policyName == "LRPW") policy= RPW;
        if (policyName == "VNS") policy= VNS;
         
    }
    
    
     node* stationList::decideNode(std::vector<node*> nodeQueue){
         
         switch(policy){
            case LTT:               
                return LTTpolicy(nodeQueue);
                break;
                
            case STT:   
                 return STTpolicy(nodeQueue);            
                break; 
                
             case MFT:   
                 return MFTpolicy(nodeQueue);        
                break;
                
            case LNFT:  
                  return LNFTpolicy(nodeQueue);            
                break;
                
            case RPW: 
                 return RPWpolicy(nodeQueue);             
                break; 
             
                 case LRPW: 
                 return LRPWpolicy(nodeQueue);             
                break; 
                
                
            case VNS:   
                            
                break;     
                
            default: 
                std::cout<<"Nothing";
                return LTTpolicy(nodeQueue); 
                break;
         
        }
     }
        
    node* stationList::LTTpolicy(std::vector<node*> nodeQueue)
    { 
         node* THEnode= nodeQueue.front();
         
         for(int i=0; i<nodeQueue.size(); i++)
         {
             if(THEnode->getValue()>nodeQueue[i]->getValue())
             {
                 THEnode=nodeQueue[i];
             }
         }
         
         return THEnode;
    }
    
    node* stationList::STTpolicy(std::vector<node*> nodeQueue)
    {   
    
      node* THEnode= nodeQueue.front();
         
         for(int i=0; i<nodeQueue.size(); i++)
         {
            if(THEnode->getValue()<nodeQueue[i]->getValue())
             {
                 THEnode=nodeQueue[i];
             }
         }
         
         return THEnode;
    
    }
    
    node* stationList::MFTpolicy(std::vector<node*> nodeQueue)
    {
    
      node* THEnode= nodeQueue.front();
         
         for(int i=0; i<nodeQueue.size(); i++)
         {
             if(THEnode->getNumFT()>nodeQueue[i]->getNumFT())
             {
                 THEnode=nodeQueue[i];
             }
         }
         
         return THEnode;
    
    }
    
    node* stationList::LNFTpolicy(std::vector<node*> nodeQueue)
    {
    
      node* THEnode= nodeQueue.front();
         
         for(int i=0; i<nodeQueue.size(); i++)
         {
             if(THEnode->getNumFT()<nodeQueue[i]->getNumFT())
             {
                 THEnode=nodeQueue[i];
             }
         }
         
         return THEnode;
    
    }
    
    node* stationList::RPWpolicy(std::vector<node*> nodeQueue)
    {
      
      node* THEnode= nodeQueue.front();
         
         for(int i=0; i<nodeQueue.size(); i++)
         {
              if(THEnode->getRPW()>nodeQueue[i]->getRPW())
             {
                 THEnode=nodeQueue[i];
             }
         }
         
         return THEnode;
      
    }
    
       node* stationList::LRPWpolicy(std::vector<node*> nodeQueue)
    {
      
      node* THEnode= nodeQueue.front();
         
         for(int i=0; i<nodeQueue.size(); i++)
         {
              if(THEnode->getRPW()<nodeQueue[i]->getRPW())
             {
                 THEnode=nodeQueue[i];
             }
         }
         
         return THEnode;
      
    }
    
    
    void stationList::setCycleTime(int time){
    
        cycleTime = time;
    
    }
//
    std::vector<station> stationList::getStationList(){
    
        return stations;
    
    }
 
     