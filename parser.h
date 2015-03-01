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

    class parser{
    
    private:
        
        std::vector<weightNode> weights;
        std::vector<dependencyNode> dependencies;
        std::string filename;
        int datasetsize;
        
    public:
        
        parser();
        parser(std::string);
        
        std::vector<weightNode> getWeightsVector();
        std::vector<dependencyNode> getDependenciesVector();
        
        void parseFile();
        
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

