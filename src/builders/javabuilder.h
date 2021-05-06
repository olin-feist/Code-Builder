#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

namespace javabuilder{
    vector<string> singletonbuilder(string name);
    vector<string> factorybuilder(string headname,string methodname,vector<string> classnames);
    vector<string> commandbuilder(string refclass,string invokerclass,vector<string> classnames);
    vector<string> observerbuilder(string classname);
    void writeFile(vector<string> v, string path, string filename);
        

}

