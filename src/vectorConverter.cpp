#include <iostream>
#include <vector>
#include "vectorConverter.h"
#include <fstream>
using namespace std;

vector<string> vectorConverter::textToVector(string path){

    fstream file;
    file.open(path);
    string line;
    vector<string> test;
    while(getline(file, line)){
        
        test.push_back(line);
    }

    return test;
}

vector<string> vectorConverter::textToVector(string path, int low, int high){

    fstream file;
    file.open(path);
    string line;
    vector<string> test;
    int count=1;
    while(getline(file, line)){
        if(count>=low&&count<=high){
            test.push_back(line);
        }
        count++;
        
    }

    return test;
}