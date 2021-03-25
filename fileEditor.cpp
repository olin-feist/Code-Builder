#include <iostream>
#include <vector>
#include <fstream>
#include "fileEditor.h"
#include "vectorConverter.h"
using namespace std;

vector<string> fileEditor::addClassName(vector<string> file, string name, string flag){
    
    
    for(int i=0;i<file.size();i++){
        if(file[i].find(flag)!=string::npos){
            file[i].replace(file[i].find(flag),flag.size(),name);
        }
        
    }

    return file;
}


vector<string> fileEditor::add(vector<string> file, vector<string> values){
    
    for(string line: values){
        file.push_back(line);
    }
    file.push_back("\n");

    return file;
}

