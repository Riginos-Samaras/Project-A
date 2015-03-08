#include "node.h"
#include "nodeGraph.h"
#include "parser.h"
#include "stationList.h"
#include <valarray>

#include <dirent.h>

using namespace::std;
void VNSpolicy(stationList);
int main(int argc, char**argv)
{
    // Prints welcome message...
    std::cout << "Welcome ...n" << std::endl;
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
    std::cout<<"Choose a benchmark:"<<std::endl;
    for(int i=2; i<benchmarks.size();i++){
                
                    std::cout<<i-1<<")"<<benchmarks[i]<<std::endl;
               
                
            }
    
    std::cout<<"Benchmark #: ";
    std::cin>>benchmarkChoice;

    }while((benchmarkChoice>25)||(benchmarkChoice<1));
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
    parser p1("data/"+benchmarks[benchmarkChoice+2]);
    datasetSize = p1.getDatasetSize();
    //Creating the graph and populating it with the parsed data
    stationList s;
    int cycleTime = 20;
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
    for(int i =0; i<s.x.getNodeList().size();i++)
    {
        if(cycleTime<s.x.getNodeList()[i].getValue())
        {
            cout<<"The cycle time should not be smaller than the maximum weight in the node graph"<<endl;
            return 10;
        }
    }
    //s.x.printNodes();
    s.x.setFollowingTasks();
  //  VNSpolicy(s);
    cout<<"------------------------"<<endl;
  
    
    if(policyChoice!=7){
        s.setPolicy(policies[policyChoice-1]);
        for(int i=0;i<datasetSize;i++)
        {
            node * decidedNode=s.decideNode(s.x.getQueue());
            s.pushTaskToStation(decidedNode); 
        }
        s.printStations();
        s.x.vectorNodeListPrinter(s.x.getNodeList());
    }
    else
        s.VNSpolicy();
    cout<<"------------------------"<<endl; 
    return 8;
}
void VNSpolicy(stationList s)
{
    stationList st1=s;
    stationList st2=s;
    int datasetsize = st1.x.getNodeList().size();
    std::vector <double> randomArray;
    
    for(int i=0;i<datasetsize;i++)
    {
        srand(time(0));
        randomArray.push_back(static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
    }
    
   
       
  
      
    for (int q=0; q<datasetsize;q++)
    {
        std::vector<node*>tempQueue = st1.x.getQueue();
        node* THEnode= tempQueue.front();
        
        for(int i=0; i<tempQueue.size(); i++)
        {
            //cout<<randomArray[THEnode->getName()-1] << randomArray[st1.x.getQueue()[i]->getName()-1];
            if(randomArray[THEnode->getName()-1] < randomArray[tempQueue[i]->getName()-1])
            {
                THEnode=tempQueue[i];
            }
        }
        cout<<endl; 
       // cout<<st1.getStationList()[1].getCycleTime()<<endl; 
        st1.x.vectorPrinter(st1.x.getQueue());
        st1.pushTaskToStation(THEnode); 
        cout<<st1.getStationList()[0].getCycleTime()<<endl;
        st1.x.checkAvailable();
        st1.x.vectorPrinter(st1.x.getQueue());
        break;
         
    }
    
    int kmax = datasetsize;
    for (int i=0; i<20;i++)
    {
        int k = 0;
        randomArray.clear();
        for(int z=0;z<datasetsize;z++)
            {
                randomArray.push_back(static_cast <double> (rand()) / static_cast <double> (RAND_MAX));
            }
        while(k<kmax)
        {
            
            
            if(k%2 ==0){//shift
            
                for(int n=0;n<k;n++){
                    double temp = randomArray.back();
                    randomArray.pop_back();
                    randomArray.insert(randomArray.begin(),temp);
                }
            }
            else{//exchange
                
                int pos1 = rand() % datasetsize;
                int pos2 = rand() % datasetsize;
                
                double temp = randomArray[pos1];
                randomArray[pos1] = randomArray[pos2];
                randomArray[pos2] = temp;
            
            }
            
            for(int i=0;i<datasetsize;i++)
                {
                   cout<<" | "<<randomArray[i];
                }
            cout<<endl;
            for (int q=0; q<datasetsize;q++)
            {
                node* THEnode= st2.x.getQueue().front();
                for(int i=0; i<st2.x.getQueue().size(); i++)
                {
                    if(randomArray[THEnode->getName()-1] < randomArray[st2.x.getQueue()[i]->getName()-1])
                    {
                        THEnode=st2.x.getQueue()[i];
                    }
                }
                st2.pushTaskToStation(THEnode);
            }
            if(st2.getStationList().size() < st1.getStationList().size())
            {
                k=kmax;
                st1=st2;
                st2=s;
            }
            k++;
        }
    }
}