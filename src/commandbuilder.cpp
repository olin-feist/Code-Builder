#include <iostream>
#include <vector>
#include <fstream>
#include "cppbuilder.h"
#include "fileEditor.h"
#include "vectorConverter.h"
using namespace std;

//cpp factory design builder
vector<string> cppbuilder::commandbuilder(string refclass,string invokerclass,vector<string> classnames){

    string path="defaultcode/cpp/command/command.cpp";
    vectorConverter convert;

    


    //get vector of file
    vector<string> filevector =  convert.textToVector(path);


    fileEditor editor;

    

    //add invokerclass name
    filevector=editor.addClassName(filevector,invokerclass,"$invokerclass");

    //get method for commands
    vector<string> classText = convert.textToVector(path,36,49);

    //setup first method already in template build
    filevector=editor.addClassName(filevector,classnames[0],"$classname");
    
    //add number of command classes to file with specific names
    for(int i=1;i<classnames.size();i++){
        

        filevector=editor.add(filevector, editor.addClassName(classText,classnames[i],"$classname"));
    }

    //add refclass name
    filevector=editor.addClassName(filevector,refclass,"$referenceclass");
    

    return filevector;
}
