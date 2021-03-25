
#include <iostream>
#include <vector>
#include "cppbuilder.h"
#include <fstream>

using namespace std;

void writeFile(vector<string> v){
    fstream file;
    file.open("newCpp.cpp");
    for(string l:v){
        file<<l;
    }

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
        
    }else if(input=="test"){
        
    }

    return 0;
}


