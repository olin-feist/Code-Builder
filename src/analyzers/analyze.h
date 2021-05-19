#include <iostream>
#include <vector>
#include <fstream>



using namespace std;
namespace pyanalyzer{
    vector<string> getInstanceVar(vector<string> file, string name);
    int getEndOfClass(vector<string> file, string name);
}


/*
To be implmented later for source code parsing of java and c++
*/
namespace javaanalyzer{}

namespace cppanalyzer{}