#include "stationList.h"
#include <time.h>
using std::cout;
using std::endl;
stationList::stationList(){
    m=10000000;
    availableStations=10000000;
}
stationList::stationList(int max){
    setMaxStations(max);
    
    
}
stationList::~stationList(){}

void stationList::insertStation(){

    station *st = new station(cycleTime);
    stations.push_back(*st);
    
}

bool stationList::pushTaskToStation(node *nd){
   // cout<<"AS:"<<availableStations<<endl;
    if(stations.empty()){
        insertStation();
        availableStations--;
    }
    if(availableStations==-1)
        {return false;}
    
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
            stations.back().insertTask(nd);
            x.removeNodeFromQueue(nd);
            availableStations--;
            if(availableStations==-1)
                { 
                return false;}
           
        }
    }

        return true;

}
 void stationList::printStations(){
     for(int i=0; i<stations.size();i++){
         cout<<i<<":";
         stations[i].printTasks();
     }
 }
 
    void stationList::setMaxStations(int smax){
        m=smax;
        availableStations=smax;
         for(int i =0; i<x.getNodeList().size();i++)
         {
            Psum=Psum+x.getNodeList()[i].getValue();
            if(Pmax<x.getNodeList()[i].getValue())
            {
                Pmax=x.getNodeList()[i].getValue();
            }
         }
         
         LB=std::max(Pmax,Psum/m);
         UB=std::max(Pmax,2*Psum/m);
    }  

    void stationList::setAvailableStations(int amax){
        availableStations=amax;
    }
    int stationList::getMaxStations(){
        return m;
    }
    void stationList::setPolicy(std::string policyName){
        
        if (policyName == "LTT") policy=LTT;
        if (policyName == "STT") policy= STT;
        if (policyName == "MFT") policy= MFT;
        if (policyName == "LNFT") policy= LNFT;
        if (policyName == "RPW") policy= RPW;
        if (policyName == "LRPW") policy= RPW;
        if (policyName == "VNS") policy= VNS;
        if (policyName == "FCFS") policy= FCFS;
        if (policyName == "Random") policy= Random;
         
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
            
           case FCFS: 
                 return FCFSpolicy(nodeQueue);             
                break;
                
           case Random: 
                 return Randompolicy(nodeQueue);             
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
    
    node* stationList::FCFSpolicy(std::vector<node*>  nodeQueue){
      
         node* THEnode= nodeQueue.front();      
         return THEnode;
      
    }
    
    node* stationList::Randompolicy(std::vector<node*>  nodeQueue){
      
         node* THEnode= nodeQueue.front();
         int i=static_cast <int> (rand())%nodeQueue.size();     
         THEnode=nodeQueue[i];     
        // cout<<THEnode->getName()<<endl;
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
        
        //st1.x.printNodes();
        //this->x.printNodes();
        
      //  st1->x.vectorPrinter(st1->x.getQueue());
         
        int datasetsize = this->x.getNodeList().size();
        
        std::vector <double> oldSolution;
        std::vector <double> newSolution;
        std::vector <double> BestSolution;
        int changed=0;
        srand(time(0));
        
        for(int i=0;i<datasetsize;i++)
            {
            
                oldSolution.push_back(static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
                
            }
    
//        for(int i=0;i<oldSolution.size();i++)
//            {
//
//                std::cout<<oldSolution[i]<<"->";
//                
//            }
//       
//                std::cout<<std::endl;
    BestSolution=oldSolution;
             
                 
              
          
                
    int kmax = datasetsize;
    for (int i=0; i<20;i++)
    {    
        this->x.initDone();
        this->initStations();
        findSolution(oldSolution);
        int oldStationLength=this->getStationList().size();
        
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
               
            this->x.initDone();
            this->initStations();
            findSolution(newSolution);
           // std::cout<<this->getStationList().size() <<"-"<< oldStationLength<<endl;
            if(this->getStationList().size() < oldStationLength)
            {
                k=kmax;
                oldSolution=newSolution;
                BestSolution=newSolution;
                changed++;
            }
            k++;
        }
    
     
    }
    
    
            this->x.initDone();
            this->initStations();
            findSolution(BestSolution);
            
            this->setBestSolution(BestSolution);
     
    }
    void stationList::initStations(){  
      stations.clear();   
    } 
    
    
    
    
    void stationList::setBestSolution(std::vector <double> bs){
        bestSolution=bs;
    }
     void stationList::setBestHeuristicSolution(std::vector <int> bs){
        bestHeuristicSolution=bs;
    }
   
    std::vector <double> stationList::printBestSolution(){
        
        std::cout.unsetf ( std::ios::floatfield ); 
        for(int i=0; i<this->bestSolution.size();i++)
        {
            if(i==bestSolution.size()-1) {
                std::cout.precision(2);
                std::cout<<bestSolution[i];}
            else{
                std::cout.precision(2);
                std::cout<<bestSolution[i]<<"->";
            }
        }
        std::cout<<std::endl;
        return bestSolution;
    }
    
    std::vector <int> stationList::printBestHeuristicSolution(){
        
        std::cout.unsetf ( std::ios::floatfield ); 
        for(int i=0; i<this->bestHeuristicSolution.size();i++)
        {
            if(i==bestHeuristicSolution.size()-1) {
                std::cout.precision(2);
                std::cout<<bestHeuristicSolution[i];}
            else{
                std::cout.precision(2);
                std::cout<<bestHeuristicSolution[i]<<"->";
            }
        }
        std::cout<<std::endl;
        return bestHeuristicSolution;
    }
    
    
     void stationList::VNSpolicy(int solution){
         if(solution==1){
            LBsolution=true;          
            setCycleTime(LB);
            cycleTime=LB;
            
         }
         if(solution==2){
            UBsolution=true;
            setCycleTime(UB);
            cycleTime=UB;
         }     
         
        int datasetsize = this->x.getNodeList().size();
        
        std::vector <double> oldSolution;
        std::vector <double> newSolution;
        std::vector <double> BestSolution;
        int changed=0;
        srand(time(0));
        
        for(int i=0;i<datasetsize;i++)
            {
            
                oldSolution.push_back(static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
                
            }
    BestSolution=oldSolution;
                      
    int kmax = datasetsize;
    for (int i=0; i<20;i++)
    {   
        
        this->x.initDone();
        this->initStations();
        findSolution(oldSolution);
        int oldStationLength=this->getStationList().size();
        
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
               
            this->x.initDone();
            this->initStations();    
            findSolution(newSolution);
            
            if(this->getStationList().size() < oldStationLength)
            {
                k=kmax;
                oldSolution=newSolution;
                BestSolution=newSolution;
                changed++;
            }
            k++;
        }
    
     
    }
    
    
            this->x.initDone();
            this->initStations();
            findSolution(BestSolution);
  
            this->setBestSolution(BestSolution);
     
    }
     
     
     int stationList::getCycleTime(){
     
         return this->cycleTime;
         
     }
     
     
     int stationList::findSolution(std::vector <double> BestSolution){
          bool enoughtStations=true;
       for (int q=0; q<this->x.getNodeList().size();q++)
           {
            
                std::vector<node*>tempQueue = this->x.getQueue();
                
                node* THEnode= tempQueue.front();
                
                //FIND MAX
                for(int i=0; i<tempQueue.size(); i++)
                {
                    //cout<<randomArray[THEnode->getName()-1] << randomArray[st1.x.getQueue()[i]->getName()-1];
                    if(BestSolution[THEnode->getName()-1] < BestSolution[tempQueue[i]->getName()-1])         
                    {
                        
                        THEnode=tempQueue[i];
                        
                    }
                    
                }   
                  
                enoughtStations=this->pushTaskToStation(THEnode); 
         }
          return 1;
     }
     
   
     
      int stationList::findHeuristicSolution(std::vector <int> BestSolution){
          bool enoughtStations=true;
          int stationWeAre=0;
          const std::string dePolicies[] = {"LTT","STT","MFT","LNFT","RPW","FCFS","Random"};
          for (int q=0; q<this->x.getNodeList().size();q++)
          {
                 
                 
                 std::vector<node*>tempQueue = this->x.getQueue();
                 
                 node* THEnode= tempQueue.front();
                // cout<<dePolicies[BestSolution[this->stations.size()]]<<"dasdasdasdsa"<<endl;
                 this->setPolicy(dePolicies[BestSolution[this->stations.size()]]);
                 
                 node * decidedNode=this->decideNode(tempQueue);

                 THEnode=decidedNode;   

                 //cout<<BestSolution[q%7]<<":POLICY:"<<dePolicies[BestSolution[q%7]]<< " node:"<<THEnode->getName()<<endl;
                 
                 enoughtStations=this->pushTaskToStation(THEnode); 
          }
          return 1;
     }
     
     
    void stationList::Heuristicpolicy(){ 
         
        int datasetsize = this->x.getNodeList().size();
   
        std::vector <int> oldSolution;
        std::vector <int> newSolution;
        std::vector <int> BestSolution;
        int changed=0;
        srand(time(0));
        
        for(int i=0;i<datasetsize;i++)
            {
            
                oldSolution.push_back(static_cast <int> (rand()%7));
                
            }
    
        for(int i=0;i<oldSolution.size();i++)
            {

                std::cout<<oldSolution[i]<<"->";
                
            }
            std::cout<<std::endl;
    BestSolution=oldSolution;
    
    int kmax = datasetsize;
    for (int i=0; i<20;i++)
    {    
        this->x.initDone();
        this->initStations();
        findHeuristicSolution(oldSolution);
        int oldStationLength=this->getStationList().size();
        
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
                int pos1 = rand() % 7;
                int pos2 = rand() % 7;
                
                double temp = newSolution[pos1];
                newSolution[pos1] = newSolution[pos2];
                newSolution[pos2] = temp;
            
            }
            }
               
            this->x.initDone();
            this->initStations();
            findHeuristicSolution(newSolution);
            
            if(this->getStationList().size() < oldStationLength)
            {
                k=kmax;
                oldSolution=newSolution;
                BestSolution=newSolution;
                changed++;
            }
            k++;
        }
    
     
    }
    
            this->x.initDone();
            this->initStations();
            findHeuristicSolution(BestSolution);
             
            this->setBestHeuristicSolution(BestSolution);
     
    }