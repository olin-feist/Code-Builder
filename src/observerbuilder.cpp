#include <iostream>
#include <vector>
#include <fstream>
#include "cppbuilder.h"
#include "fileEditor.h"
#include "vectorConverter.h"
using namespace std;

//cpp factory design builder
vector<string> cppbuilder::observerbuilder(string classname){

    string path="defaultcode/cpp/observer/observer.cpp";
    vectorConverter convert;

    


    //get vector of file
    vector<string> filevector =  convert.textToVector(path);


    fileEditor editor;

    
    //add classname name
    filevector=editor.addClassName(filevector,classname,"$classname");

   
    

    return filevector;
}
