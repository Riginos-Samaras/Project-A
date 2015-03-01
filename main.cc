#include "node.h" 
#include "nodeGraph.h" 
#include "parser.h"
#include "stationList.h"
using namespace::std;

int main(int argc, char**argv) {
    // Prints welcome message...
    std::cout << "Welcome ...\n" << std::endl;
    
    //creates an instance of a parser object.
    //construction overload to get the name of the file as an input.
    int datasetSize=0;
    
    parser p1("data/BOWMAN8.IN2");
    datasetSize = p1.getDatasetSize();
    //Creating the graph and populating it with the parsed data
    
    stationList s;
     for(int i=0; i<p1.getWeightsVector().size();i++){
        s.x.insertNode(p1.getWeightsVector()[i].name,p1.getWeightsVector()[i].value);
    }
    for(int i=0; i<p1.getDependenciesVector().size();i++){
        s.x.insertEdge(p1.getDependenciesVector()[i].left,p1.getDependenciesVector()[i].right);
    }
    //
    
   //s.x.printNodes();
    s.x.setFollowingTasks();
    
    cout<<"------------------------"<<endl;
     
   
   
    
   
  
    
   
    //s.x.vectorPrinter(s.x.getQueue());
   // s.x.vectorNodeListPrinter(s.x.getNodeList());
    //s.printStations();
   s.setPolicy("LTT"); 
    for(int i=0;i<datasetSize;i++){
        node * decidedNode=s.decideNode(s.x.getQueue());
        
        s.pushTaskToStation(s.x.getQueue().front());
        
        s.x.vectorPrinter(s.x.getQueue());
        s.printStations();
        s.x.vectorNodeListPrinter(s.x.getNodeList());
    }
        s.printStations();
            cout<<"------------------------"<<endl;
       s.x.printNodes();
    return 0;
}
