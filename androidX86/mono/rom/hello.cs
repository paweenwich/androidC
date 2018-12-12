using System;
using zlib;
 
public class HelloWorld
{
    static public void Main ()
    {
        Console.WriteLine("Hello Mono World 2");
	Console.WriteLine(zlibConst.version());
    }

    static public int Test1()
    {
	return 1;
    }
}

