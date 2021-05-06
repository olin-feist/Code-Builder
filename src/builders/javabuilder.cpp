#include <iostream>
#include <vector>
#include <fstream>
#include "javabuilder.h"
#include "../fileEditor.h"
#include "../vectorConverter.h"
using namespace std;





//cpp factory observer builder
vector<string> javabuilder::observerbuilder(string classname){

    string path="../defaultcode/Java/observer/observer.java";
    

    


    //get vector of file
    vector<string> filevector =  vectorConverter::textToVector(path);


    

    
    //add classname name
    filevector=fileEditor::addClassName(filevector,classname,"$classname");

   
    

    return filevector;
}

//cpp singleton builder
vector<string> javabuilder::singletonbuilder(string name){

    string path="../defaultcode/Java/singleton/singleton.java";
    
    vector<string> file = vectorConverter::textToVector(path);

    
    return fileEditor::addClassName(file,name,"$classname");
}

//factory builder
vector<string> javabuilder::factorybuilder(string headname,string methodname,vector<string> classnames){

    string path="../defaultcode/Java/factory/factory.java";
    
    //get method for factory
    vector<string> classText = vectorConverter::textToVector(path,5,10);


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
vector<string> javabuilder::commandbuilder(string refclass,string invokerclass,vector<string> classnames){

    string path="../defaultcode/Java/command/commnd.java";
    
    //get vector of file
    vector<string> filevector =  vectorConverter::textToVector(path);


    //add invokerclass name
    filevector=fileEditor::addClassName(filevector,invokerclass,"$invokerclass");

    //get method for commands
    vector<string> classText = vectorConverter::textToVector(path,25,36);

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

//create .cpp file
void javabuilder::writeFile(vector<string> v, string path, string filename){
    ofstream file(path+"\\"+filename+".java");

    for(string l:v){
        file<<l<<endl;
    }
    file.close();
}



