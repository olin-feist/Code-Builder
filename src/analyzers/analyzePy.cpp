#include <iostream>
#include <vector>
#include <fstream>
#include "analyze.h"
#include "..\vectorConverter.h"

using namespace std;

vector<string> pyanalyzer::getInstanceVar(vector<string> file, string name){
    vector<string> v;
    //remove lines with no charecters or notes
    for(int i=0;i<file.size();i++){
        //check if its only whitespaces
        bool whitespaces=true;
        for(int j=0;j<file[i].size();j++){
            string line=file[i];
            if(line[j]!=' ')
                whitespaces=false;
        }

        if(whitespaces)
            file.erase(file.begin()+i);
    }

    for(int i=0;i<file.size();i++){
        
        if(file[i].find("#")!= string::npos)
            file.erase(file.begin()+i);
    }


    //loop through file
    for(int i=0;i<file.size();i++){
        string line=file[i];
        cout<<line<<endl;
        //find class def
        if(line.find("class") != string::npos){
            
            //check if name matches
            if(line.find(name) != string::npos){
                
                //loop through class
                for(int j=i+1;j<file.size();j++){
                    line=file[j];
                    //make sure its still within class
                    if(line.find("    ") != string::npos){
                        //find constructor
                        if(line.find("__init__") != string::npos){
                            for(int k=j+1;k<file.size();k++){
                                line=file[k];
                                if(line.find("self.") != string::npos){
                                    if(line.find("        ") != string::npos){
                                        
                                        v.push_back(line.substr(line.find("self.")+5,((line.find("="))-(line.find("self.")+5))));
                                    }
                                }else{
                                    break;
                                }
                            }
                        }
                    }else{
                        break;
                    }
                }
                
            }
        }
    } 

    return v;    
}


