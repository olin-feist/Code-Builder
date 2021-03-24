#include <iostream>
#include <vector>
#include "vectorConverter.h"
#include <fstream>
using namespace std;

vector<string> vectorConverter::textToVector(string path){
    fstream myfile;
    myfile.open (path);
    string line;
    vector<string> test;
    while(getline(myfile, line)){
        test.push_back(line);
    }

    return test;
}