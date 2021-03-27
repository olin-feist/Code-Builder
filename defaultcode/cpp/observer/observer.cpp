#include <iostream>
#include <vector>
using namespace std;

//subject class
class $classname {
    vector<Observer*> observers; 

  public:

    void attach(Observer *obs) {
        observers.push_back(obs);
    }

    void notify(){
        for (int i = 0; i < observers.size(); i++)
            observers[i]->update();
    }
};

//observer class
class Observer {

    $classname *model;
    
  public:
    Observer($classname *mod) {
        model = mod;
        model->attach(this);
    }

    void update(){

    }
};
