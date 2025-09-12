using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {

            /*
            Color color = Color.Red | Color.White; //cervena a bila
            Console.WriteLine("XXXX");
            if (color == Color.Red)
            {
                Console.WriteLine("Color is red");
                Console.WriteLine(color.ToString());
                Console.WriteLine((int)color);
                //
            }
            */

            //-----------

            Auto a1 = new Auto(500000);
            Auto a2 = new Auto(400000);
            Auto a3 = new Auto(300000);

            Console.WriteLine(a1.getIDAuta());
            Console.WriteLine(a2.getIDAuta());
            Console.WriteLine(a3.getIDAuta());

            //---------- Lab 2.4, 2.5 


        }
    }

    [Flags()]
    enum Color : long
    {
        Blue = 1,
        Red = 2,
        Green = 4,
        White = 8
    }


}
