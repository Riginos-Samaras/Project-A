/* 
 * File:   station.h
 * Author: cutingedge1
 *
 * Created on February 11, 2015, 10:24 PM
 */

#ifndef STATION_H
#define	STATION_H

class station{

    int cycleTime;
    int idleTime;
    int stationTime;
    
    vector<node*> tasks;
    
    void getCycleTime();
    void setCycleTime(int);
    void getIdleTime();
    void setIdleTime(int);
    void getStationTime();
    void setStationTime();
    


}

#endif	/* STATION_H */

