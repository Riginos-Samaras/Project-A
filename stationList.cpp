#include "stationList.h"
using std::cout;
using std::endl;
stationList::stationList(){}

void stationList::insertStation(){

    station *st = new station();
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
    

 enum string_code {
    LTF,
    eBarney,
    eWilma,
    eBetty
};

string_code hashit (std::string const& inString) {
    if (inString == "LTF") return LTF;
    if (inString == "Barney") return eBarney;
}

    void stationList::policy(std::string policyName){
        
        switch(hashit(policyName)){
            case LTF:
                cout<<"LFT";                
                break;
            default: 
                cout<<"Nothing";
                break;
         
        }
        
        
        
        
    
    }
    
    
     node* decideNode(std::vector<node*> nodeQueue){
         node* decidedNode;
//         for(int i=0;);
//         nodeQueue[1]
//                
     }