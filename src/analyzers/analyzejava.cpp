#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "analyze.h"

#include "..\vectorConverter.h"

using namespace std;


vector<string> javaanalyzer::getClassAttributes(string path){
    
    system(("cd .. && javap -private src\\"+path+" > src\\cache\\javadecomp.txt").c_str());
    
    vector<string> file=vectorConverter::textToVector("..\\src\\cache\\javadecomp.txt");
    
    vector<string> ret;

    for(string line:file)
        cout<<line<<endl;

    for(int i=0;i<file.size();i++){
        string line = file[i];
        
        if(line.find("class")!=string::npos&&line.find("//")==string::npos){

            for(int j=i+1;j<getEndOfClass(file,i+1);j++){
                line = file[j];
                
                if(line.find("(")==string::npos&&line.find("(")==string::npos){
                    
                    vector<string> result; 
                    istringstream iss(line); 
                    for(string line; iss >> line; ) 
                        result.push_back(line); 

                    for(string s: result){
                        if(s.compare("public")!=0&&s.compare("private")!=0&&s.compare("protected")!=0){
                            if(s.compare("final")==0){
                                break;
                            }else{
                               
                                s.erase(remove(s.begin(), s.end(), ';'), s.end());
                                cout<<s<<endl;

                                ret.push_back(s);
                            }
                        }
                    }
                }
            }
        }
    }
   
    return ret;

}

int javaanalyzer::getEndOfClass(vector<string> file,int index){
    
    string line = file[index];
    
    if(line.find("{") != string::npos){
        int i=index+1;
        return getEndOfClass(file,getEndOfClass(file,i)+1);
    }else if(line.find("}") != string::npos){
        return index;
    }else{
        int i=index+1;
        return getEndOfClass(file,i);
    }
    
}


int javaanalyzer::getClasIndex(vector<string> file,string s){
    for(int i=0;i<file.size();i++){
        string line = file[i];
        if(line.find("class")!=string::npos&&line.find(s)!=string::npos&&line.find("//")==string::npos)
            return i;
    }

    return -1;
}




