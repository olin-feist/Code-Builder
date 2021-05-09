#subject class
class Subject:
    
    def __init__(self):
        self.observers= []
        
    def attach(self, observer):
        self.observers.append(observer)
        
    def notify(self):
        for observer in self.observers:
            observer.update()

#observer class            
class Observer:
    
    def __init__(self,obj):
        self.subject = obj
        obj.attach(self)
        
    def update(self):
        pass


