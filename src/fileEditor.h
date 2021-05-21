#include <iostream>
#include <vector>
#include <fstream>
#include <wx/wx.h>
#include <wx/treectrl.h>
using namespace std;

namespace fileEditor{
    
        vector<string> addClassName(vector<string> file, string name, string flag);
        vector<string> add(vector<string> file, vector<string> values);
        wxTreeCtrl* getClassTree(string path, wxTreeCtrl *tree);
        void addPyGetters(string path);
        void addPySetters(string path);
        void addJavaGetters(string path);
        void addJavaSetters(string path);
        
};