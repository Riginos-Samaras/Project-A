/*
 * Copyright (c) 2009-2010, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Oracle nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "node.h" 
#include "nodeGraph.h" 
#include "parser.h"
using namespace::std;

int main(int argc, char**argv) {
    // Prints welcome message...
    std::cout << "Welcome ...\n" << std::endl;
    parser p1("data.txt");
    p1.parseFile();
    
    nodeGraph x; 
     for(int i=0; i<p1.getWeightsVector().size();i++){
        x.insertNode(p1.getWeightsVector()[i].name,p1.getWeightsVector()[i].value);
    }
    for(int i=0; i<p1.getDependenciesVector().size();i++){
        x.insertEdge(p1.getDependenciesVector()[i].left,p1.getDependenciesVector()[i].right);
    }
     
    x.printNodes();
    //x.in_nodes.push_back(10);
    //x.in_nodes.push_back(5);
    //std::cout<<x.in_nodes.back();
    // Prints arguments...
//    std::cout<<x.get_name() <<x.get_value()<< x.is_done();
   // x.insert_input_node(1,1)
 
    
    return 0;
}
