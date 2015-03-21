/* 
 * File:   station.h
 * Author: cutingedge1
 *
 * Created on February 11, 2015, 10:24 PM
 */

#ifndef STATION_H
#define	STATION_H

#include <vector>
#include <string>
#include <iostream>
#include "nodeGraph.h"

class station{
private:
    int cycleTime;
    int idleTime;
    int stationTime;
    int stationID;
    
    std::vector<node*> tasks;
public:
    station();
    station(int);
    int getCycleTime();
    void setCycleTime(int);
    
    int getStationID();
    void setStationID(int);
    
    int getIdleTime();
    void setIdleTime(int);
    
    int getStationTime();
    void setStationTime(int);
    
    bool canInsert(node*);
    
    void insertTask(node*);
    
    void printTasks();
    
    std::vector<node*> getTasks();
    
    int findST();
};

#endif	/* STATION_H */

