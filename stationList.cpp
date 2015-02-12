
#include "stationList.h"

stationList::stationList(){}

void stationList::insertStation(){

    station *st = new station();
    stations.push_back(*st);
    
}

void stationList::pushTaskToStation(node nd){

    if(stations.empty())
        insertStation();
    if(stations.back().canInsert(nd))
        stations.back().insertTask(nd);
    else{
    
    
    
    }


}

void stationList::something(std::vector <node> &q){

    

}