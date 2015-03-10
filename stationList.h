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
#include "nodeGraph.h"


 enum string_policy {
    LTT,
    STT,
    MFT,
    LNFT,
    RPW,
    LRPW,
    VNS
};


class stationList{

private:
    std::vector<station> stations;
    string_policy policy;
    std::vector <double> bestSolution;
    int cycleTime;
    int m;
    int availableStations;

public:
    nodeGraph x; 
    stationList();
    stationList(int);
    ~stationList();
    void insertStation();
    bool pushTaskToStation(node*); 
    void printStations();
    void setPolicy(std::string);
    void initStations();
    void setMaxStations(int);
    void setAvailableStations(int);
    int getMaxStations();
    node* decideNode(std::vector<node*>);
    node* LTTpolicy(std::vector<node*>);
    node* STTpolicy(std::vector<node*>);
    node* MFTpolicy(std::vector<node*>);
    node* LNFTpolicy(std::vector<node*>);
    node* RPWpolicy(std::vector<node*>);
    node* LRPWpolicy(std::vector<node*>);
    void VNSpolicy();
    std::vector<station> getStationList();
    void setBestSolution(std::vector <double>);
    std::vector <double> printBestSolution();
    void setCycleTime(int);



};

#endif	/* STATIONLIST_H */