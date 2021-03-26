#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class cppbuilder{
    public:
        vector<string> singletonbuilder(string name);
        vector<string> factorybuilder(string headname,string methodname,vector<string> classnames);
        vector<string> commandbuilder(string refclass,string invokerclass,vector<string> classnames);
        
};