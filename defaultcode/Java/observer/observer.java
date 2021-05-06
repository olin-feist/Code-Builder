//subject class
public class $classname {
    List<Observer> observers; 

    void attach(Observer obs) {
        observers.add(obs);
    }

    void notify(){
        for (int i=0; i<observers.size(); i++){
            observers[i].update();
        }
            
    }
}

//observer class
class Observer {

    public $classname model;
    

    public Observer($classname mod) {
        model = mod;
        model.attach(this);
    }

    public void update(){

    }
}