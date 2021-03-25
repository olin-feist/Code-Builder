#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class fileEditor{
    public:
        vector<string> addClassName(vector<string> file, string name, string flag);
        vector<string> add(vector<string> file, vector<string> values);
        
};