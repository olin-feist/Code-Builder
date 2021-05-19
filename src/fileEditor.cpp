#include <iostream>
#include <vector>
#include <fstream>
#include "fileEditor.h"
#include "vectorConverter.h"
#include <wx/wx.h>
#include <wx/treectrl.h>
#include "analyzers/analyze.h"
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


void fileEditor::addPyGetters(string path){
    vector<string> file = vectorConverter::textToVector(path);

    vector<string> classnames;
    for(string line:file){
        if(line.find("class ")!=string::npos&&line.find("#")==string::npos){
            classnames.push_back(line);
        }
    }

    for(string s:classnames){
        vector<string> ivar = pyanalyzer::getInstanceVar(file,s);

        vector<string> getter;
        getter.clear();
        for(string i:ivar){
            getter.push_back("");
            getter.push_back("\t# getter method");
            getter.push_back("\tdef get_"+i+"(self):");
            getter.push_back("\t\treturn self."+i);
            getter.push_back("");

        }
        
        file.insert(file.begin() + pyanalyzer::getEndOfClass(file,s)-1 ,getter.begin(),getter.end());
        ivar.clear();
    }
    
    ofstream ofile(path, ofstream::trunc);
    for(string line:file){
        ofile<<line<<endl;
    }
    ofile.close();

}

void fileEditor::addPySetters(string path){
    vector<string> file = vectorConverter::textToVector(path);

    vector<string> classnames;
    for(string line:file){
        if(line.find("class ")!=string::npos&&line.find("#")==string::npos){
            classnames.push_back(line);
        }
    }

    for(string s:classnames){
        vector<string> ivar = pyanalyzer::getInstanceVar(file,s);

        vector<string> getter;
        getter.clear();
        for(string i:ivar){
            getter.push_back("");
            getter.push_back("\t# setter method");
            getter.push_back("\tdef set_"+i+"(self,a):");
            getter.push_back("\t\tself."+i+"=a");
            getter.push_back("");

        }
        
        file.insert(file.begin() + pyanalyzer::getEndOfClass(file,s)-1 ,getter.begin(),getter.end());
        ivar.clear();
    }
    
    ofstream ofile(path, ofstream::trunc);
    for(string line:file){
        ofile<<line<<endl;
    }
    ofile.close();

}


int findend(vector<string> file,int index){
    string line = file[index];
    if(line.find("{") != string::npos){
        return findend(file,index++);
    }else if(line.find("}") != string::npos){
        return index;
    }else{
        return findend(file,index);
    }
    
}
