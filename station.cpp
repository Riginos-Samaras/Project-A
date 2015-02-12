#include "station.h"


station::station(){
    
    stationTime = 0;
    cycleTime= 100;    
}
station::station(int cycle_time){
    
    stationTime = 0;
    cycleTime= cycle_time;
    
}

int station::getCycleTime(){
    
    return cycleTime;
}

int station::getIdleTime(){
    
    return idleTime;
}

int station::getStationID(){
    
    return stationID;
}

int station::getStationTime(){
    
    return stationTime;
}

void station::setCycleTime(int time){

    cycleTime = time;
}

void station::setIdleTime(int time){

    idleTime = time;
}

void station::setStationID(int id){

    stationID = id;
}

void station::setStationTime(int time){

    stationTime = time;
    setIdleTime(cycleTime - stationTime);
}

bool station::canInsert(node nd){

    return idleTime>=nd.getValue();

}

void station::insertTask(node nd){

    tasks.push_back(&nd);
    setStationTime(getStationTime() + nd.getValue()); //updates station time & idle time
    
    
}