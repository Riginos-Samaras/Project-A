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
    VNS
};


class stationList{

private:
    std::vector<station> stations;
    string_policy policy;

public:
    nodeGraph x; 
    stationList();
    void insertStation();
    void pushTaskToStation(node*); 
    void printStations();
    void setPolicy(std::string);
    node* decideNode(std::vector<node*>);
    node* LTTpolicy(std::vector<node*>);
    node* STTpolicy(std::vector<node*>);
    node* MFTpolicy(std::vector<node*>);
    node* LNFTpolicy(std::vector<node*>);
    node* RPWpolicy(std::vector<node*>);
    node* VNSpolicy(std::vector<node*>);



};

#endif	/* STATIONLIST_H */