class $classname
{
    //single instance
    private static $classname instance = null;
  
  
    // private constructor
    private $classname()
    {

    }
  
    //get instance
    public static $classname getInstance()
    {
        if (instance == null)
            instance = new $classname();
  
        return instance;
    }
}