#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class vectorConverter{
    public:
        vector<string> textToVector(string path);
        vector<string> textToVector(string path, int low, int high);
        
};