#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "fileEditor.h"
#include "vectorConverter.h"
#include <wx/wx.h>
#include <wx/treectrl.h>
#include "analyzers/analyze.h"

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
            getter.push_back("    # getter method");
            getter.push_back("    def get_"+i+"(self):");
            getter.push_back("        return self."+i);
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
            getter.push_back("    # setter method");
            getter.push_back("    def set_"+i+"(self,a):");
            getter.push_back("        self."+i+"=a");
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

void fileEditor::addJavaGetters(string path){
    cout<<path<<endl;
    system(("cd .. && javac -d src\\cache "+path).c_str());
    
    vector<string> file = vectorConverter::textToVector(path);
    vector<string> classnames;

    for(string line:file){
        vector<string> result; 
        if(line.find("class ")!=string::npos&&line.find("//")==string::npos){
            
            istringstream iss(line); 
            for(string line; iss >> line; ) 
                result.push_back(line); 
            for(int i=0;i<result.size();i++){
                string s=result[i];
                if(s=="class"){
                    result[i+1].erase(remove(result[i+1].begin(), result[i+1].end(), '{'), result[i+1].end());
                    result[i+1].erase(remove(result[i+1].begin(), result[i+1].end(), ' '), result[i+1].end());
                    classnames.push_back(result[i+1]);
                }
            }
            
        }
        result.clear();
    }
    
    for(string s:classnames){
        
        vector<string> ivar = javaanalyzer::getClassAttributes("cache\\"+s+".class");

        vector<string> getter;
        getter.clear();
        for(int i=0;i<ivar.size();i+=2){
            getter.push_back("");
            getter.push_back("    // Get "+ivar[i+1]);
            getter.push_back("    public "+ivar[i]+" get"+ivar[i+1]+"() {");
            getter.push_back("        return "+ivar[i+1]+";");
            getter.push_back("    }");
            getter.push_back("");

        }
     
        cout<<javaanalyzer::getEndOfClass(file,javaanalyzer::getClasIndex(file,s)+1)<<endl;
            
        file.insert(file.begin() + javaanalyzer::getEndOfClass(file,javaanalyzer::getClasIndex(file,s)+1),getter.begin(),getter.end());
        ivar.clear();
    }
    
    ofstream ofile(path, ofstream::trunc);
    for(string line:file){
        ofile<<line<<endl;
    }
    ofile.close();

}