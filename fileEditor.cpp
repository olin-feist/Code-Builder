#include <iostream>
#include <vector>
#include <fstream>
#include "fileEditor.h"
#include "vectorConverter.h"
using namespace std;

vector<string> fileEditor::addClassName(string path, string name){
    vectorConverter converter;
    vector<string> a = converter.textToVector(path);
    
    for(string temp: a){
        if(temp.find("$classname")!=string::npos){
            temp.replace(temp.find("$classname"),10,name);
        }
        cout<<temp<<endl;
        
    }

    return a;
}

