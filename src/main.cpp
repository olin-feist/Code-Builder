
#include <iostream>
#include <vector>
#include "cppbuilder.h"
#include <fstream>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/filepicker.h>
#include <wx/combo.h>
#include <wx/listctrl.h>
#include <wx/odcombo.h>


#include "BuildFrame.h"
#include "MainFrame.h"

using namespace std;



class MyApp : public wxApp{
    public:
        virtual bool OnInit();
};



wxIMPLEMENT_APP(MyApp);



MainFrame *mainframe = new MainFrame("Code Builder", wxPoint(100, 100), wxSize(800, 800));



//main method for gui
bool MyApp::OnInit(){
    
    //FreeConsole();
    mainframe->Show(true);
    
    /*
    cppbuilder build;

    string input;
    cin>>input;
    if(input=="singleton"){
        string name;
        cout<<"Class Name: "<<endl;
        cin>>name;
        writeFile(build.singletonbuilder(name));
        
    }else if(input=="factory"){
        string headname;
        string methodname;
        //get main class name
        cout<<"Main Class Name: "<<endl;
        cin>>headname;
        //get method name
        cout<<"Method Name: "<<endl;
        cin>>methodname;
        //get classes names
        cout<<"Classes Name: "<<endl;
        string classname;
        vector<string> v;
        while(classname!="end"){
            cin>>classname;
            if(classname!="end"){
                v.push_back(classname);
            }
        }

        writeFile(build.factorybuilder(headname,methodname,v));

    }else if(input=="command"){
        string refclass;
        string invokerclass;
        vector<string> classnames;

        cout<<"Reference Class Name: "<<endl;
        cin>>refclass;

        cout<<"Invoker Class  Name: "<<endl;
        cin>>invokerclass;       
        string classname;
        while(classname!="end"){
            cout<<"Command Classes Name: "<<endl;
            
            cin>>classname;
            if(classname!="end"){
                classnames.push_back(classname);
            }
        }

         writeFile(build.commandbuilder(refclass,invokerclass,classnames));
         

    }else if(input=="observer"){
        string classname;
        cout<<"Subject Class Name"<<endl;
        cin>>classname;
        writeFile(build.observerbuilder(classname));
    }*/

    
    return true;
}


