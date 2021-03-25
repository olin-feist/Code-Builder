#include <iostream>

using namespace std;

class $classname {
    $classname *instance;

    
    //constructor
    $classname() {
    }


    public:
        //method to get instance
        $classname *getInstance() {
            if (!instance)
                instance = new $classname;

            return instance;
        }

        //$getters

        //$setters

};