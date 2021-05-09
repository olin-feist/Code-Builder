from abc import ABC, abstractmethod

#command interface
class Command(ABC):

    @abstractmethod
    def execute(self):
        pass

class $referenceclass:
    pass

#invoker class
class $invokerclass:

    def __init__(self, command):
        self.cmd = command

    def ButtonPressed(self):
        self.cmd.execute()

#command class
class $classname(Command):
   
    def __init__(self, refclass):
        self.ref = refclass

    def execute(self):
       pass

       