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
    if ((dir = opendir ("benchmarks")) != NULL) {
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
    for(int i=3; i<benchmarks.size();i++){
                
                    std::cout<<i-2<<")"<<benchmarks[i]<<std::endl;
               
                
            }
    
    std::cout<<"Benchmark #: ";
    std::cin>>benchmarkChoice;
    
    }while((benchmarkChoice>25)||(benchmarkChoice<1));
    cout<<endl<<"You have chose: "<<benchmarks[benchmarkChoice+2];
    const string policies[] = {"LTT","STT","MFT","LNFT","RPW","LRPW","FCFS","Random","VNS","Heuristic"};
    int policyChoice =0;
    do{
    cout<<endl;
    cout<<"====Choose Policy===="<<endl;
    
    for(int i=0; i<10;i++){
                
                    std::cout<<i+1<<")"<<policies[i]<<std::endl;
               
                
            }
    
    cout<<"Policy #: ";
    cin>>policyChoice;
    }while((policyChoice>10)||(policyChoice<1));
    std::vector<dataset1Node> dataset1;
    std::vector<dataset2Node> dataset2;
    parser p1("benchmarks/"+benchmarks[benchmarkChoice+2],Algorithm);
    if(Algorithm==1)
        dataset1=p1.getDataset1();
    else
        dataset2=p1.getDataset2();
    
    datasetSize = p1.getDatasetSize();
    stationList s;
    int cycleTime = 0;
    int optimumStations=0;
    int optumumCycleTime=0;
    int m=0;
    
    //Creating the graph and populating it with the parsed data

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
                cout<<dataset1[benchmarkChoice-1].cycletimes[0]<<"The cycle time should not be smaller than the maximum weight in the node graph("<<Pmax<<")"<<endl; 
                
                for(int k=0; k<dataset1.size();k++){
                    if(benchmarks[benchmarkChoice+2]==dataset1[k].name){
                        
                        cout<<";"<<dataset1[benchmarkChoice+2].name<<endl;
                        cout<<";"<<dataset1[k].name<<endl;
                        cycleTime = dataset1[k].cycletimes[0];
                        
                    }
                }
                
                optimumStations = dataset1[benchmarkChoice-1].optimum[0];
                cout<<"Cycle time #: "<<cycleTime<<endl;
               
                //cin>>cycleTime;

        }while(Pmax>cycleTime);          
        s.setCycleTime(cycleTime);
    
          cout<<"------------------------"<<endl;

          

          if(policyChoice<9){
              s.setPolicy(policies[policyChoice-1]);
              for(int i=0;i<datasetSize;i++)
              {
                  node * decidedNode=s.decideNode(s.x.getQueue());
                  s.pushTaskToStation(decidedNode); 
                  
              }
              cout<<"Problems and optimal solutions\nPreced.\t\t\ngraph\t\tc\tm\tm*\n--------------------------"<<endl; 
              cout<<benchmarks[benchmarkChoice+2]<<"\t"<<cycleTime<<"\t"<<s.getStationList().size()<<"\t"<<optimumStations<<endl;
          }
          else if(policyChoice==9){
              s.VNSpolicy();
              cout<<"Problems and optimal solutions\nPreced.\t\t\ngraph\t\tc\tm\tm*\n--------------------------"<<endl; 
              cout<<benchmarks[benchmarkChoice+2]<<"\t"<<cycleTime<<"\t"<<s.getStationList().size()<<"\t"<<optimumStations<<endl;
              cout<<endl<<"Optimal solutions vector\n--------------------------"<<endl;
              s.printBestSolution();
          }
          else if(policyChoice==10){
             s.Heuristicpolicy();             
              cout<<"Problems and optimal solutions\nPreced.\t\t\ngraph\t\tc\tm\tm*\n--------------------------"<<endl; 
              cout<<benchmarks[benchmarkChoice+2]<<"\t"<<cycleTime<<"\t"<<s.getStationList().size()<<"\t"<<optimumStations<<endl;
             cout<<endl<<"Optimal solutions vector\n--------------------------"<<endl;
             s.printBestHeuristicSolution();
          }

    }

     if(Algorithm==2){
        
         //LB =max(p ,p m)
        
            
                //optimumcycleTime = dataset2[benchmarkChoice-1].cycletimes[0];
                //m = dataset2[benchmarkChoice-1].optimum[0];
            bool found=false;
            for(int k=0; k<dataset2.size();k++){
                    if(benchmarks[benchmarkChoice+2]==dataset2[k].name){
                        found=true;
                        cout<<";"<<benchmarks[benchmarkChoice+2]<<endl;
                        cout<<";"<<dataset2[k].name<<endl;
                        m = dataset2[k].stations[0];
                        
                    }
                }
            if (!found){
                cout<<"There no values for the selected benchmark in the dataset"<<endl;
                cout<<endl;
                string shallContinue;
                cout<<"Shall we continue?(Y/N)"<<endl;
                cin>>shallContinue; 
                if(shallContinue=="N"){break;}else{continue;}
            
            }
                
                cout<<"Stations #: "<<m;      
                

           
        
         int solution=0;
         bool LBsolution=false;
         bool UBsolution=false;   
         bool MIDCsolution=false;
       if(policyChoice>0&&policyChoice<9) 
            do{ 
                     cout<<"Choose a solution :\n1)LB\n2)UB\n3)MIDC"; 
                     cout<<"\nSolution #:";      
                     cin>>solution;

             }while(solution!=1&&solution!=2&&solution!=3);  

         int LB=std::max(Pmax,Psum/m);
         int UB=std::max(Pmax,2*Psum/m);
         int midc=(LB+UB)/2;
         cout<<"LB:"<<LB<<" UB:"<<UB<<" midc:"<<midc<<" Pmax:"<<Pmax<<" Psum:"<<Psum<<endl;  
         s.setMaxStations(m);
        
         
         if(solution==1){
            LBsolution=true;          
            s.setCycleTime(LB);
            cycleTime=LB;
         }
         if(solution==2){
            UBsolution=true;
            s.setCycleTime(UB);
            cycleTime=UB;
         }
         if(solution==3){
            MIDCsolution=true;
            s.setCycleTime(midc);
            cycleTime=midc;
         }
         int minc=LB;
         int maxc=UB;
         
    
         cout<<"------------------------"<<endl;
         int rememberedOne=0;
         bool enoughtStations=true;

          if(policyChoice<9){
              s.setPolicy(policies[policyChoice-1]);
              if(LBsolution||UBsolution){
                    for(int i=0;i<datasetSize;i++)
                    {
                        node * decidedNode=s.decideNode(s.x.getQueue());
                        enoughtStations=s.pushTaskToStation(decidedNode);

                      if(LBsolution) {
                        if(!enoughtStations){
                            i=-1;
                            LB=LB+1;
                            cycleTime=LB;
                            s.setAvailableStations(m);
                            s.setCycleTime(LB); 
                            s.initStations();
                            s.x.initDone();
                        } 
                      }

                      if(UBsolution){
                         if(enoughtStations&&(i==(datasetSize-1))){  
                            i=-1;
                            UB=UB-1;
                            cycleTime=UB;         
                            s.setAvailableStations(m);
                            s.setCycleTime(UB); 
                            s.initStations();
                            s.x.initDone();
                            rememberedOne=UB;
                        } 

                      }
                          if(!enoughtStations&&i==datasetSize-1){                
                              s.setCycleTime(rememberedOne);
                              break;
                        } 
                       }  
              }
              else if(MIDCsolution){   
                  while (maxc >= minc) {
                     midc = (maxc+minc)/2;
                     s.setCycleTime(midc);
                    //NODE INITIALIZATION
                     s.initStations();
                     s.x.initDone();
                     //RUN THE GRAPH
                     for(int i=0;i<datasetSize;i++)
                     {
                         node * decidedNode=s.decideNode(s.x.getQueue());
                         s.pushTaskToStation(decidedNode);
                     }
                     
                    cout<<"min:"<<minc<<" mid:"<<midc<<" max:"<<maxc<<" :size"<<s.getStationList().size()<<" m:"<<m<<endl;  
                     //case we got a small station number then we have to decrease cycle time in order for our algorithm to get a bigger number of startions
                     if(s.getStationList().size() > m){
                      minc = midc +1;
                     }else if(s.getStationList().size() < m){
                      maxc = midc -1;
                    }
                     else if(s.getStationList().size() == m){
                         maxc--;
                     }
                            
                  }
              }
              cout<<"Problems and optimal solutions\nPreced.\t\t\ngraph\t\tm\tc\tc*\n--------------------------"<<endl; 
              if(LBsolution||MIDCsolution)
                 cout<<benchmarks[benchmarkChoice+2]<<"\t"<<s.getStationList().size()<<"\t"<<s.getCycleTime()<<"\t"<<optumumCycleTime<<endl;
              if(UBsolution)
                 cout<<benchmarks[benchmarkChoice+2]<<"\t"<<s.getStationList().size()-1<<"\t"<<s.getCycleTime()+1<<"\t"<<optumumCycleTime<<endl;
         
          }
          else if(policyChoice==9){
              
             // do{
                 s.initStations();
                 s.x.initDone();
                 s.setCycleTime(LB); 
                 s.setMaxStations(m);
                 s.VNSpolicy(); 
                 LB=LB+1;
             // }while(s.getStationList().size()!=dataset2[benchmarkChoice-1].optimum[0]);
              cout<<"Problems and optimal solutions\nPreced.\t\t\ngraph\t\tm\tc\tc*\n--------------------------"<<endl; 
              cout<<benchmarks[benchmarkChoice+2]<<"\t"<<s.getStationList().size()<<"\t"<<s.getCycleTime()<<"\t"<<optumumCycleTime<<endl;
              cout<<endl<<"Optimal solutions vector\n--------------------------"<<endl;
              s.printBestSolution();
          }
          else if(policyChoice==10){          
             s.setCycleTime(LB); 
             s.setMaxStations(m);
             s.Heuristicpolicy();             
             cout<<"Problems and optimal solutions\nPreced.\t\t\ngraph\t\tm\tc\tc*\n--------------------------"<<endl; 
             cout<<benchmarks[benchmarkChoice+2]<<"\t"<<s.getStationList().size()<<"\t"<<s.getCycleTime()<<"\t"<<optumumCycleTime<<endl;
             cout<<endl<<"Optimal solutions vector\n--------------------------"<<endl;
             s.printBestHeuristicSolution();
          }
    }
    string shallContinue;
    cout<<"Shall we continue?(Y/N)"<<endl;
    cin>>shallContinue; 
    if(shallContinue=="N"){break;}else{continue;}
    }while(true);
    
    return 8;
}
