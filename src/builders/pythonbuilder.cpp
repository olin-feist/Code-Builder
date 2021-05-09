#include <iostream>
#include <vector>
#include <fstream>
#include "pythonbuilder.h"
#include "../fileEditor.h"
#include "../vectorConverter.h"
using namespace std;





//python factory observer builder
vector<string> pythonbuilder::observerbuilder(string classname){

    string path="../defaultcode/python/observer/observer.py";
    

    //get vector of file
    vector<string> filevector =  vectorConverter::textToVector(path);

    
    //add classname name
    filevector=fileEditor::addClassName(filevector,classname,"$classname");

   
    return filevector;
}

//python singleton builder
vector<string> pythonbuilder::singletonbuilder(string name){

    string path="../defaultcode/python/singleton/singleton.py";
    
    vector<string> file = vectorConverter::textToVector(path);

    
    return fileEditor::addClassName(file,name,"$classname");
}

//python factory builder
vector<string> pythonbuilder::factorybuilder(string headname,string methodname,vector<string> classnames){

    string path="../defaultcode/python/factory/factory.py";
    
    //get method for factory
    vector<string> classText = vectorConverter::textToVector(path,11,14);


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

//python command design builder
vector<string> pythonbuilder::commandbuilder(string refclass,string invokerclass,vector<string> classnames){

    string path="../defaultcode/python/command/command.py";
    
    //get vector of file
    vector<string> filevector =  vectorConverter::textToVector(path);


    //add invokerclass name
    filevector=fileEditor::addClassName(filevector,invokerclass,"$invokerclass");

    //get method for commands
    vector<string> classText = vectorConverter::textToVector(path,22,29);

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

//create .py file
void pythonbuilder::writeFile(vector<string> v, string path, string filename){
    ofstream file(path+"\\"+filename+".py");

    for(string l:v){
        file<<l<<endl;
    }
    file.close();
}



