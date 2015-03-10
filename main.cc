#include "node.h"
#include "nodeGraph.h"
#include "parser.h"
#include "stationList.h"

#include <iostream>
#include <stdio.h>
#include <valarray>

#include <algorithm>    // std::max
#include <dirent.h>

using namespace::std;
void VNSpolicy(stationList);
int main(int argc, char**argv)
{
    do{
    // Prints welcome message...
    std::cout << "Welcome to ALBP1 and ALBP2 algorithms" << std::endl;
    int Algorithm=0;do{
    cout<<"Choose algorithm:\n"<<"1)ALBP1 2)ALBP2\nAlgorithm #:";cin>>Algorithm;}while(Algorithm!=1&&Algorithm!=2);
   
    //creates an instance of a parser object.
    //construction overload to get the name of the file as an input.
    int datasetSize=0;
    std::vector<string> benchmarks;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("data")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        benchmarks.push_back(ent->d_name);
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
      return EXIT_FAILURE;
    }
    
    int benchmarkChoice=-1;
    do{
    std::cout<<endl<<"Choose a benchmark:"<<std::endl;
    for(int i=2; i<benchmarks.size();i++){
                
                    std::cout<<i-1<<")"<<benchmarks[i]<<std::endl;
               
                
            }
    
    std::cout<<"Benchmark #: ";
    std::cin>>benchmarkChoice;
    
    }while((benchmarkChoice>25)||(benchmarkChoice<1));
    cout<<endl<<"You have chose: "<<benchmarks[benchmarkChoice+1];
    const string policies[] = {"LTT","STT","MFT","LNFT","RPW","LRPW","VNS"};
    int policyChoice =0;
    do{
    cout<<endl;
    cout<<"====Choose Policy===="<<endl;
    
    for(int i=0; i<7;i++){
                
                    std::cout<<i+1<<")"<<policies[i]<<std::endl;
               
                
            }
    
    cout<<"Policy #: ";
    cin>>policyChoice;
    }while((policyChoice>7)||(policyChoice<1));
    
    parser p1("data/"+benchmarks[benchmarkChoice+1]);
    datasetSize = p1.getDatasetSize();
    stationList s;
    int cycleTime = 3786;   
    int m=0;
    
    //Creating the graph and populating it with the parsed data

    s.setCycleTime(cycleTime);
    for(int i=0; i<p1.getWeightsVector().size();i++)
    {
        s.x.insertNode(p1.getWeightsVector()[i].name,p1.getWeightsVector()[i].value); 
    }
    for(int i=0; i<p1.getDependenciesVector().size();i++)
    {
        s.x.insertEdge(p1.getDependenciesVector()[i].left,p1.getDependenciesVector()[i].right);   
    }
    //
    
    int Pmax=0;  
    int Psum=0; 
    for(int i =0; i<s.x.getNodeList().size();i++)
    {
        Psum=Psum+s.x.getNodeList()[i].getValue();
        if(Pmax<s.x.getNodeList()[i].getValue())
        {
            Pmax=s.x.getNodeList()[i].getValue();
        }
    }
    
    //s.x.printNodes();
    s.x.setFollowingTasks();
    if(Algorithm==1){
        do{
                cout<<"The cycle time should not be smaller than the maximum weight in the node graph("<<Pmax<<")"<<endl;       
                cout<<"Cycle time #: ";
                cin>>cycleTime;

        }while(Pmax>cycleTime);       
        s.setCycleTime(cycleTime);
    
          cout<<"------------------------"<<endl;

          

          if(policyChoice!=7){
              s.setPolicy(policies[policyChoice-1]);
              for(int i=0;i<datasetSize;i++)
              {
                  node * decidedNode=s.decideNode(s.x.getQueue());
                  s.pushTaskToStation(decidedNode); 
              }
              cout<<"Problems and optimal solutions\nPreced.	  c\ngraph   (given)	 m*\n--------------------------"<<endl; 
              cout<<benchmarks[benchmarkChoice+1]<<"\t"<<cycleTime<<"\t"<<s.getStationList().size()<<endl;
          }
          else{
              s.VNSpolicy();
              cout<<"Problems and optimal solutions\nPreced.	  c\ngraph   (given)	 m*\n--------------------------"<<endl; 
              cout<<benchmarks[benchmarkChoice+1]<<"\t"<<cycleTime<<"\t"<<s.getStationList().size()<<endl;
              cout<<endl<<"Optimal solutions vector\n--------------------------"<<endl;
              s.printBestSolution();
          }
    }
     if(Algorithm==2){
         //LB =max(p ,p m)
        do{ 
                cout<<"Stations #:";      
                cin>>m;

        }while(m<=0);    
        
        
         int LB=std::max(Pmax,Psum/m);
         int UB=std::max(Pmax,2*Psum/m);
         cout<<"LB:"<<LB<<" UB:"<<UB<<" Pmax:"<<Pmax<<" Psum:"<<Psum<<endl;  
         
         cout<<"\nmaxstations:"<<s.getMaxStations()<<endl;  
         s.setMaxStations(m);
         s.setCycleTime(LB);
         cycleTime=LB;
         
         cout<<"\nmaxstations:"<<s.getMaxStations()<<endl;  
    
          cout<<"------------------------"<<endl;

         bool istrue=true;

          if(policyChoice!=7){
              s.setPolicy(policies[policyChoice-1]);
              for(int i=0;i<datasetSize;i++)
              {
                  node * decidedNode=s.decideNode(s.x.getQueue());
                  istrue=s.pushTaskToStation(decidedNode);
                  if(!istrue){
                      
                  cout<<"i:"<<i<<" istrue:"<<istrue<<" cycletime:"<<cycleTime<<""<<endl;
                      i=0;
                      LB=LB+1;
                      cycleTime=LB;
                      s.initStations();
                      s.setAvailableStations(m);
                      s.x.initDone();
                      s.setCycleTime(LB);                  
                  }
                 
              }
              cout<<"Problems and optimal solutions\nPreced.	  m\ngraph   (given)	 c*\n--------------------------"<<endl; 
              cout<<benchmarks[benchmarkChoice+1]<<"\t"<<cycleTime<<"\t"<<s.getStationList().size()<<endl;
          }
          else{
              s.VNSpolicy();
              cout<<"Problems and optimal solutions\nPreced.	  m\ngraph   (given)	 c*\n--------------------------"<<endl; 
              cout<<benchmarks[benchmarkChoice+1]<<"\t"<<cycleTime<<"\t"<<s.getStationList().size()<<endl;
              cout<<endl<<"Optimal solutions vector\n--------------------------"<<endl;
              s.printBestSolution();
          }
    }
    string shallContinue;
    cout<<"Shall we continue?(Y/N)"<<endl;
    cin>>shallContinue; 
    if(shallContinue=="N"){break;}else{continue;}
    }while(true);
    
    return 8;
}
