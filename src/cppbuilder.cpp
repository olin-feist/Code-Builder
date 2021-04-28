#include <iostream>
#include <vector>
#include <fstream>
#include "cppbuilder.h"
#include "fileEditor.h"
#include "vectorConverter.h"
using namespace std;





//cpp factory observer builder
vector<string> cppbuilder::observerbuilder(string classname){

    string path="../defaultcode/cpp/observer/observer.cpp";
    

    


    //get vector of file
    vector<string> filevector =  vectorConverter::textToVector(path);


    

    
    //add classname name
    filevector=fileEditor::addClassName(filevector,classname,"$classname");

   
    

    return filevector;
}

//cpp singleton builder
vector<string> cppbuilder::singletonbuilder(string name){

    string path="defaultcode/cpp/singleton/singleton.cpp";
    
    vector<string> file = vectorConverter::textToVector(path);

    
    return fileEditor::addClassName(file,name,"$classname");
}

//factory builder
vector<string> cppbuilder::factorybuilder(string headname,string methodname,vector<string> classnames){

    string path="../defaultcode/cpp/factory/factory.cpp";
    
    //get method for factory
    vector<string> classText = vectorConverter::textToVector(path,9,13);


    //get vector of file
    vector<string> filevector =  vectorConverter::textToVector(path);


    

    //setup first method already in template build
    filevector=fileEditor::addClassName(filevector,classnames[0],"$classname");
    
    //add number of factory classes to file with specific names
    for(int i=1;i<classnames.size();i++){
        

        filevector=fileEditor::add(filevector, fileEditor::addClassName(classText,classnames[i],"$classname"));
    }

    //add head named
    filevector=fileEditor::addClassName(filevector,headname,"$headname");

    //add method name
    filevector=fileEditor::addClassName(filevector,methodname,"$methodname");


    
    

    return filevector;
}

//cpp command design builder
vector<string> cppbuilder::commandbuilder(string refclass,string invokerclass,vector<string> classnames){

    string path="defaultcode/cpp/command/command.cpp";
    

    


    //get vector of file
    vector<string> filevector =  vectorConverter::textToVector(path);


    

    

    //add invokerclass name
    filevector=fileEditor::addClassName(filevector,invokerclass,"$invokerclass");

    //get method for commands
    vector<string> classText = vectorConverter::textToVector(path,36,49);

    //setup first method already in template build
    filevector=fileEditor::addClassName(filevector,classnames[0],"$classname");
    
    //add number of command classes to file with specific names
    for(int i=1;i<classnames.size();i++){
        

        filevector=fileEditor::add(filevector, fileEditor::addClassName(classText,classnames[i],"$classname"));
    }

    //add refclass name
    filevector=fileEditor::addClassName(filevector,refclass,"$referenceclass");
    

    return filevector;
}

void cppbuilder::writeFile(vector<string> v, string path, string filename){
    ofstream file(path+"\\"+filename+".cpp");

    for(string l:v){
        file<<l<<endl;
    }
    file.close();
}



