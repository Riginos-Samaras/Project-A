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
    
void stationList::something(std::vector <node> &q){

    

}