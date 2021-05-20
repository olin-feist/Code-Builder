//command interface
interface Command {
   void execute();
}

class $referenceclass  {
	
}

// Invoker 
class $invokerclass {

    public Command cmd;

	void setCommand(Command *cmd) {
		this.cmd = cmd;
	}

	void buttonPressed() {
		cmd.execute();
	} 

}

// command class
class $classname implements Command {

    private $referenceclass rclass;

    $classname($referenceclass  rclass){
        this.rclass=rclass;
    }

    public void execute() {
    }
}
