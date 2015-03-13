/* 
 * File:   parser.h
 * Author: michael panayiotou
 *
 * Created on February 10, 2015, 7:56 PM
 */

#ifndef PARSER_H
#define	PARSER_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>

#ifdef	__cplusplus
extern "C" {
#endif
    
    struct weightNode {
         int value;
         int name;
    } ;
    
    struct dependencyNode {
         int left;
         int right;
    } ;

    struct dataset1Node {
        std::string name;
         std::vector<int> cycletimes;
         std::vector<int> optimum;
    } ;
    
    struct find_name : std::unary_function<dataset1Node, bool> {
    std::string name;
    find_name(std::string name):name(name) { }
    bool operator()(dataset1Node const& m) const {
        return m.name == name;
    }
};


    
    class parser{
    
    private:
        
        std::vector<weightNode> weights;
        std::vector<dependencyNode> dependencies;
        std::vector<dataset1Node> dataset1Vec;
        std::string filename;
        std::string datasetName;
        int datasetsize;
        
    public:
        
        parser();
        parser(std::string, int);
        
        std::vector<weightNode> getWeightsVector();
        std::vector<dependencyNode> getDependenciesVector();
        
        void parseFile();
        
        void parseDataSetALBP1();
        void parseDataSetALBP2();
        
        int getDatasetSize();
        void setDatasetSize(int);
        
        void insertWeightToVector(int,int);
        void insertDependencyToVector(int,int);
        

        void printWeightsVector();
        void printDependenciesVector();
        
    
    };



#ifdef	__cplusplus
}
#endif

#endif	/* PARSER_H */

