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
    parser p1("BOWMAN8.txt");
    
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
    
    
     
   // x.printNodes();
   
    
   
    s.x.checkAvailable();
    
    s.pushTaskToStation(s.x.getQueue().front());
    s.x.vectorPrinter(s.x.getQueue());
    s.x.vectorNodeListPrinter(s.x.getNodeList());
    s.printStations();
     s.x.checkAvailable();
    s.pushTaskToStation(s.x.getQueue().front());
   s.x.checkAvailable();
    s.x.vectorPrinter(s.x.getQueue());
    s.printStations();
    
    //x.in_nodes.push_back(10);
    //x.in_nodes.push_back(5);
    //std::cout<<x.in_nodes.back();
    // Prints arguments...
//    std::cout<<x.get_name() <<x.get_value()<< x.is_done();
   // x.insert_input_node(1,1)
 
      
    return 0;
}
