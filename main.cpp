
#include <iostream>
#include <vector>
#include "vectorConverter.h"
#include <fstream>

using namespace std;


int main(){
    

    string a = "test.cpp";
    vectorConverter convert;
    vector<string> s = convert.textToVector(a);

    for(string temp:s){
        cout<<temp<<endl;
    }

    return 0;
}