#include <iostream>
#include <vector>
#include <fstream>
#include "cppbuilder.h"
#include "fileEditor.h"
#include "vectorConverter.h"
using namespace std;

vector<string> cppbuilder::singletonbuilder(string name){

    string path="defaultcode/cpp/singleton/singleton.cpp";
    vectorConverter convert;
    vector<string> file = convert.textToVector(path);

    fileEditor editor;
    return editor.addClassName(file,name,"$classname");
}
