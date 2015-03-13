#include "parser.h"
using std::cout;
using std::endl;
using std::ifstream;
const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";
const char* const DELIMITER2 = "\t";


parser::parser()
{
    filename="data.txt";
    
    parser::parseFile();
}
parser::parser(std::string fn, int type)
{
    filename=fn;
    if(type==1)
        datasetName = "datasets/dataset-1.txt";
    else
        datasetName = "datasets/dataset-2.txt"; 
    parser::parseFile();
    parser::parseDataSetALBP1();
}

void parser::parseDataSetALBP1(){
    std::string datasetsNames[] = {"Arcus1", "Arcus2", "Barthol2", "Barthold", "Bowman", "Buxey", "Gunther", "Hahn", "Heskiaoff", "Jackson", "Jaeschke", "Kilbridge", "Lutz1", "Lutz2", "Lutz3", "Mansoor", "Mertens", "Mitchell", "Mukherje", "Roszieg", "Sawyer", "Scholl", "Tonge", "Warnecke", "Wee-mag"};
    std::string realDatasetsNames[] = {"ARC83.IN2", "ARC111.IN2", "BARTHOL2.IN2", "BARTHOLD.IN2", "BOWMAN8.IN2", "BUXEY.IN2", "GUNTHER.IN2", "HAHN.IN2", "HESKIA.IN2", "JACKSON.IN2", "JAESCHKE.IN2", "KILBRID.IN2", "LUTZ1.IN2", "LUTZ2.IN2", "LUTZ3.IN2", "MANSOOR.IN2", "MERTENS.IN2", "MITCHELL.IN2", "MUKHERJE.IN2", "ROSZIEG.IN2", "SAWYER30.IN2", "SCHOLL.IN2", "TONGE70.IN2", "WARNECKE.IN2", "WEE-MAG.IN2"};
        // create a file-reading object
    ifstream fin;
    fin.open(datasetName);
    // open a file
    if (!fin.good())
    exit(11);
    // read each line of the file
    
    int k =0;
    while (!fin.eof())
  {
    // read an entire line into memory
    char buf2[MAX_CHARS_PER_LINE];
    fin.getline(buf2, MAX_CHARS_PER_LINE);
    
    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index
    
    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
    // parse the line
    token[0] = strtok(buf2, DELIMITER2); // first token
    while(k==0){
        
    if(strcmp(token[0],"--------------------------")){
        
        k=1;
    }
    fin.getline(buf2, MAX_CHARS_PER_LINE);
   
    token[0] = strtok(buf2, DELIMITER2);
    fin.getline(buf2, MAX_CHARS_PER_LINE);
    fin.getline(buf2, MAX_CHARS_PER_LINE);
 
    }
    
    
    if (token[0]) // zero if line is blank
    {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        token[n] = strtok(0, DELIMITER2); // subsequent tokens
        if (!token[n]) break; // no more tokens
      }
    }
   
   // cout<<token[0]<<endl;
        for(int j=0;j<25;j++){
        if(token[0]==datasetsNames[j]){
            std::vector<dataset1Node>::iterator it;
            it = std::find_if(dataset1Vec.begin(), dataset1Vec.end(), 
         find_name(realDatasetsNames[j]));
            if (it != dataset1Vec.end()){
                it->cycletimes.push_back(atoi(token[1]));
                it->optimum.push_back(atoi(token[2]));
            }
            else{
                dataset1Node node;
                node.name=realDatasetsNames[j];
                node.cycletimes.push_back(atoi(token[1]));
                node.optimum.push_back(atoi(token[2]));
                dataset1Vec.push_back(node);
            }
            
        
        }
            
        }
        
      //cout << "Token[" << i << "] = " << token[i] << endl;
    
   // cout << endl;
  }
//print vector
//    
//    for(int i=0;i<dataset1Vec.size();i++)
//    {
//        cout<<dataset1Vec[i].name<<":"<<endl;
//        for(int j=0;j<dataset1Vec[i].optimum.size();j++)
//        {
//            cout<<"\t c = "<<dataset1Vec[i].cycletimes[j]<<"\t"<<"m* = "<<dataset1Vec[i].optimum[j]<<endl;
//        }
//    
//    }
}

std::vector<weightNode> parser::getWeightsVector()
{
    return weights;
}
std::vector<dependencyNode> parser::getDependenciesVector()
{
    return dependencies;
}
void parser::setDatasetSize(int size){

    datasetsize = size;
    

}
int parser::getDatasetSize(){

    return datasetsize;

}
void parser::insertWeightToVector(int name,int value)
{
    weightNode node;
    node.value=value;
    node.name=name;
    weights.push_back(node);
}
void parser::insertDependencyToVector(int left,int right)
{
    dependencyNode node;
    node.left=left;
    node.right=right;
    dependencies.push_back(node);
}
void parser::printWeightsVector()
{
    for (int count = 0;
    count < weights.size();
    count++) //For Loop to Display All Products
    {
        cout<< weights[count].name << "," << weights[count].value << endl;
    }
    cout << endl;
}
void parser::printDependenciesVector()
{
    for (int count = 0;
    count < dependencies.size();
    count++) //For Loop to Display All Products
    {
        cout<< dependencies[count].left << "," << dependencies[count].right << endl;
    }
    cout << endl;
}
void parser::parseFile()
{
    int first_flag=0;
    //to get the first token
    int num_of_data=0;
    // create a file-reading object
    ifstream fin;
    fin.open(filename);
    // open a file
    if (!fin.good())
    exit(10);
    // read each line of the file
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);
    // parse the line into blank-delimited tokens
    int n = 0;
    // a for-loop index
    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {};
    // initialize to 0
    // parse the line
    token[0] = strtok(buf, DELIMITER);
    // first token
    if (first_flag==0)
    {
        cout<<endl<<"Number of input data: ";
        cout<<token[0];
        cout<<endl;
        
        num_of_data = atoi(token[0]);
        
        datasetsize = num_of_data;
        
        // cast the number of input data from char* to int
        first_flag = 1;
    }
    for(int k=1;k<=num_of_data;k++)
    {
        
        char buf2[MAX_CHARS_PER_LINE];
        fin.getline(buf2, MAX_CHARS_PER_LINE);
        // parse the line into blank-delimited tokens
        int n = 0;
        // a for-loop index
        // array to store memory addresses of the tokens in buf
        const char* token1[MAX_TOKENS_PER_LINE] =
        {
        }
        ;
        // initialize to 0
        token1[0] = strtok(buf2, DELIMITER);
        // first token
        if (token1[0]) // zero if line is blank
        {
            for (n = 1;
            n < MAX_TOKENS_PER_LINE;
            n++)
            {
                token1[n] = strtok(0, DELIMITER);
                // subsequent tokens
                if (!token1[n]) break;
                // no more tokens
            }
        }
        parser::insertWeightToVector(k,atoi(token1[0]));
    }
 
    while(1)
    {
        char buf3[MAX_CHARS_PER_LINE];
        fin.getline(buf3, MAX_CHARS_PER_LINE);
        // parse the line into blank-delimited tokens
        
        
        // a for-loop index
        // array to store memory addresses of the tokens in buf
        const char* token2[MAX_TOKENS_PER_LINE] =
        {
        }
        ;
        // initialize to 0
        token2[0] = strtok(buf3, ",");
        int temp = atoi(token2[0]);
        // first token
        token2[1] = strtok(0, ",");
         
        if(temp==-1){
            
        break;}
       
        parser::insertDependencyToVector(atoi(token2[0]),atoi(token2[1]));
    }
}