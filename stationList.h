/* 
 * File:   stationList.h
 * Author: dimitriosboglou
 *
 * Created on February 11, 2015, 11:45 PM
 */

#ifndef STATIONLIST_H
#define	STATIONLIST_H
#include <vector>
#include <string>
#include <iostream>
#include "station.h"
class stationList{

private:
    std::vector<station> stations;
    
public:
    stationList();
    void insertStation();
    void pushTaskToStation(node);
    void something(std::vector<node> &);



};

#endif	/* STATIONLIST_H */

