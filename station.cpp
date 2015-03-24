#include "station.h"
using std::cout;
using std::endl;

station::station(){
    
    cycleTime= 1000;  
    setStationTime(0);
      
}
station::station(int cycle_time){
    
    
    cycleTime= cycle_time;
    setStationTime(0);
    
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

bool station::canInsert(node* nd){
    
    return idleTime>=nd->getValue();
    

}

void station::insertTask(node* nd){
    
    tasks.push_back(nd);
    
    setStationTime(getStationTime() + nd->getValue()); //updates station time & idle time
    
    
}


void station::printTasks(){
     for(int i=0; i<tasks.size();i++){
                if(i==(tasks.size()-1))
                    cout<<tasks[i]->getName()<<endl;
                else
                    cout<<tasks[i]->getName()<<"->";
                
            }
}
void station::printTasks(std::ofstream& myfile){
     for(int i=0; i<tasks.size();i++){
                if(i==(tasks.size()-1)){
                    cout<<tasks[i]->getName()<<endl;
                    myfile<<tasks[i]->getName()<<endl;
                    
                }
                else{
                    cout<<tasks[i]->getName()<<"->";
                    myfile<<tasks[i]->getName()<<"->";
                }
            }
}

std::vector<node*> station::getTasks(){

    return tasks;
    
}


int station::findST(){
    int ST=0;
    for(int j =0; j<tasks.size();j++)
    {
        ST=ST+tasks[j]->getValue();
    }
    return ST;
 
}