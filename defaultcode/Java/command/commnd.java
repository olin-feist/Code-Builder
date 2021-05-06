//command interface
public interface Command {
   void execute();
}

public class $referenceclass  {
	
}

// Invoker 
public class $invokerclass {

    public Command *cmd;

	void setCommand(Command *cmd) {
		this.cmd = cmd;
	}

	void buttonPressed() {
		cmd.execute();
	} 

}

// command class
public class $classname implements Command {

    private $referenceclass rclass;

    $classname($referenceclass  *rclass){
        this.rclass=rclass;
    }

    public void execute() {
    }
}
