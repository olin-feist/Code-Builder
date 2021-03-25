#include <iostream>
#include <vector>
#include <fstream>
#include "cppbuilder.h"
#include "fileEditor.h"
using namespace std;

vector<string> cppbuilder::singletonbuilder(string name){
    string path="defaultcode/cpp/singleton/singleton.cpp";
    fileEditor editor;
    return editor.addClassName(path,name);




}
