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
#include <fstream>
#include "station.h"
#include "nodeGraph.h"
#include <math.h>


 enum string_policy {
    LTT,
    STT,
    MFT,
    LNFT,
    RPW,
    FCFS,
    Random,
    LRPW,
    VNS
};


class stationList{

private:
    std::vector<station> stations;
    string_policy policy;
    std::vector <double> bestSolution;
    std::vector <int> bestHeuristicSolution;
    int cycleTime;
    int m;
    int availableStations;
    int LB;
    int UB;
    int Psum;
    int Pmax;
    bool LBsolution=false;
    bool UBsolution=false;
public:
    nodeGraph x; 
    stationList();
    stationList(int);
    ~stationList();
    void insertStation();
    bool pushTaskToStation(node*); 
    void printStations();
    void printStations(std::ofstream& myfile);
    
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
    node* FCFSpolicy(std::vector<node*>);
    node* Randompolicy(std::vector<node*>);
    node* LRPWpolicy(std::vector<node*>);
    void VNSpolicy();
    void Heuristicpolicy();
    void VNSpolicy(int);
    std::vector<station> getStationList();
    void setBestSolution(std::vector <double>);
    void setBestHeuristicSolution(std::vector <int>);
    std::vector <double> printBestSolution();
    std::vector <int> printBestHeuristicSolution();
    void setCycleTime(int);
    int getCycleTime();
    int findBT();
    double findSX();
    int findSolution(std::vector <double> );
    int findHeuristicSolution(std::vector <int>);


};

#endif	/* STATIONLIST_H */