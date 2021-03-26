#include <iostream>

using namespace std;

// Command Interface
class Command
{
public:
	virtual void execute();
};
 
// Receiver Class
class $referenceclass 
{
public:
	
}; 

// Invoker 
class $invokerclass {

public:
	void setCommand(Command *cmd) {
		this->cmd = cmd;
	}

	void buttonPressed() {
		cmd->execute();
	} 

private:
	Command *cmd;

};

// Command class
class $classname : public Command {

    public:

        $classname($referenceclass  *rclass){
            this->rclass=rclass;
        }

        void execute(){}

    private:
        $referenceclass  *rclass;
};
 
 