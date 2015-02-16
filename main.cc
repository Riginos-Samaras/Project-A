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
    parser p1("data/SCHOLL.IN2");
    
    //Creating the graph and populating it with the parsed data
    
    stationList s;
     for(int i=0; i<p1.getWeightsVector().size();i++){
        s.x.insertNode(p1.getWeightsVector()[i].name,p1.getWeightsVector()[i].value);
    }
    for(int i=0; i<p1.getDependenciesVector().size();i++){
        s.x.insertEdge(p1.getDependenciesVector()[i].left,p1.getDependenciesVector()[i].right);
    }
    //
    
   
    s.x.setFollowingTasks();
    
    
     
 s.x.printNodes();
   
    
   
  
    
    s.pushTaskToStation(s.x.getQueue().front());
    s.x.vectorPrinter(s.x.getQueue());
    s.x.vectorNodeListPrinter(s.x.getNodeList());
    s.printStations();
    
    for(int i=0;i<296;i++){
        cout<<endl<<"#"<<i<<"repeated"<<endl;
    s.pushTaskToStation(s.x.getQueue().front());
    s.x.vectorPrinter(s.x.getQueue());
    s.printStations();
    s.x.vectorNodeListPrinter(s.x.getNodeList());
    }

      
    return 0;
}
