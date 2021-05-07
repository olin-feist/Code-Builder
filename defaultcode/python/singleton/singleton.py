class $classname:

   __instance = None
   
    #get instance method
   @staticmethod 
   def getInstance():

      if $classname.__instance == None:
         $classname()

      return $classname.__instance

   def __init__(self):

      if $classname.__instance != None:

      else:
         $classname.__instance = self