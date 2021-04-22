#include <iostream>
#include <vector>
#include <fstream>
#include "cppbuilder.h"
#include "fileEditor.h"
#include "vectorConverter.h"
using namespace std;

//cpp factory design builder
vector<string> cppbuilder::factorybuilder(string headname,string methodname,vector<string> classnames){

    string path="../defaultcode/cpp/factory/factory.cpp";
    vectorConverter convert;
    //get method for factory
    vector<string> classText = convert.textToVector(path,9,13);


    //get vector of file
    vector<string> filevector =  convert.textToVector(path);


    fileEditor editor;

    //setup first method already in template build
    filevector=editor.addClassName(filevector,classnames[0],"$classname");
    
    //add number of factory classes to file with specific names
    for(int i=1;i<classnames.size();i++){
        

        filevector=editor.add(filevector, editor.addClassName(classText,classnames[i],"$classname"));
    }

    //add head named
    filevector=editor.addClassName(filevector,headname,"$headname");

    //add method name
    filevector=editor.addClassName(filevector,methodname,"$methodname");


    
    

    return filevector;
}
