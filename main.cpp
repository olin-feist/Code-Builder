
#include <iostream>
#include <vector>
#include "src/cppbuilder.h"
#include <fstream>

using namespace std;

void writeFile(vector<string> v){
    ofstream file("newCpp.cpp");

    for(string l:v){
        file<<l<<endl;
    }
    file.close();
}

int main(){
    cppbuilder build;

    string input;
    cin>>input;
    if(input=="singleton"){
        string name;
        cout<<"Class Name: "<<endl;
        cin>>name;
        writeFile(build.singletonbuilder(name));
        
    }else if(input=="factory"){
        string headname;
        string methodname;
        //get main class name
        cout<<"Main Class Name: "<<endl;
        cin>>headname;
        //get method name
        cout<<"Method Name: "<<endl;
        cin>>methodname;
        //get classes names
        cout<<"Classes Name: "<<endl;
        string classname;
        vector<string> v;
        while(classname!="end"){
            cin>>classname;
            if(classname!="end"){
                v.push_back(classname);
            }
        }
        writeFile(build.factorybuilder(headname,methodname,v));
    }

    return 0;
}


