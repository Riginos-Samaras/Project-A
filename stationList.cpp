#include "stationList.h"
#include <time.h>
using std::cout;
using std::endl;
stationList::stationList(){}
stationList::~stationList(){}

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
 
    void stationList::VNSpolicy(){
    
       
        stationList st1;
        
        st1.x.insertNode(69,69);
        
        //st1->x.printNodes();
      //  this->x.printNodes();
        
      //  st1->x.vectorPrinter(st1->x.getQueue());
         
        int datasetsize = this->x.getNodeList().size();
        
        std::vector <double> oldSolution;
        std::vector <double> newSolution;

        srand(time(0));
        
        for(int i=0;i<datasetsize;i++)
            {
            
                oldSolution.push_back(static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
                
            }
    
        for(int i=0;i<oldSolution.size();i++)
            {

                std::cout<<oldSolution[i]<<"->";
                
            }
       
                std::cout<<std::endl;
        
        for (int q=0; q<datasetsize;q++)
           {
            
                std::vector<node*>tempQueue = this->x.getQueue();
                
                node* THEnode= tempQueue.front();
                
                //FIND MAX
                for(int i=0; i<tempQueue.size(); i++)
                {
                    //cout<<randomArray[THEnode->getName()-1] << randomArray[st1.x.getQueue()[i]->getName()-1];
                    if(oldSolution[THEnode->getName()-1] < oldSolution[tempQueue[i]->getName()-1])         
                    {
                        
                        THEnode=tempQueue[i];
                        
                    }
                    
                }   
                  
                this->pushTaskToStation(THEnode); 
              
               // st1->x.vectorNodeListPrinter(st1->x.getNodeList());
         }
                this->printStations(); 
                
                
                this->x.initDone();
                this->initStations();
                
          for (int q=0; q<datasetsize;q++)
           {
            
                std::vector<node*>tempQueue = this->x.getQueue();
                
                node* THEnode= tempQueue.front();
                
                //FIND MAX
                for(int i=0; i<tempQueue.size(); i++)
                {
                    //cout<<randomArray[THEnode->getName()-1] << randomArray[st1.x.getQueue()[i]->getName()-1];
                    if(oldSolution[THEnode->getName()-1] < oldSolution[tempQueue[i]->getName()-1])         
                    {
                        
                        THEnode=tempQueue[i];
                        
                    }
                    
                }   
                  
                this->pushTaskToStation(THEnode); 
              
               // st1->x.vectorNodeListPrinter(st1->x.getNodeList());
         }
                   
                this->printStations(); 
                
                 int kmax = datasetsize;
    for (int i=0; i<20;i++)
    {   
        int k = 0;
        while(k<kmax)
        {
            newSolution=oldSolution;
            if(k%2 ==0){//shift
            
                for(int n=0;n<k;n++){
                    double temp = newSolution.back();
                    newSolution.pop_back();
                    newSolution.insert(newSolution.begin(),temp);
                }
                
            }
            else{//exchange
             for(int e=0;e<k;e++){
                int pos1 = rand() % datasetsize;
                int pos2 = rand() % datasetsize;
                
                double temp = newSolution[pos1];
                newSolution[pos1] = newSolution[pos2];
                newSolution[pos2] = temp;
            
            }
            }
            /*
                    std::cout<<std::endl;
                    std::cout<<std::endl;
                    
                    std::cout<<k<<": ";
                         for(int i=0;i<newSolution.size();i++)
            {

                std::cout<<newSolution[i]<<"->";
                
            }
            */
           
               /*
            if(st2->getStationList().size() < st1->getStationList().size())
            {
                k=kmax;
                st1=st2;
                st2=this;
                oldSolution=newSolution;
            }*/
            k++;
        }
        
    }
                 
     
    }
    void stationList::initStations(){  
      stations.clear();   
    } 