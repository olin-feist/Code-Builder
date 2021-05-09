#include <iostream>
#include <vector>
#include <fstream>
#include "fileEditor.h"
#include "vectorConverter.h"
#include <wx/wx.h>
#include <wx/treectrl.h>
#include <sstream>

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

wxTreeCtrl* fileEditor::getClassTree(string path, wxTreeCtrl *tree){
    //get file convert to vector
    vector<string> file = vectorConverter::textToVector(path);

    //get file name from path
    stringstream test(path);
    string segment;
    vector<string> seglist;

    while(getline(test, segment, '\\'))
    {
        seglist.push_back(segment);
    }

    //add filename to tree
    wxTreeItemId rootId=tree->AddRoot(seglist[seglist.size()-1]);

    //loop through file
    for(string s:file){
        
        //get line of string divided by spaces
        vector<string> result; 
        istringstream iss(s); 

        for(string s; iss >> s;){
            result.push_back(s); 
        }

        //loop through line
        for(int i=0;i<result.size();i++){
            if(((result[0].substr(0,1)).compare("#"))&&((result[0].substr(0,2)).compare("//"))){
                //if class add class name to tree
                if(!(result[i].compare("class"))){
                    tree->AppendItem(rootId, result[i+1]);
                }
            }
            

        }
    }

    return tree;

}

