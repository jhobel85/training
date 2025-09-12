using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Closure
{
    class Program
    {
        private static int j = 0;

        delegate void MyDelegate();

        delegate MyDelegate MyAnotherDelegate(string FirstName, string LastName);

        delegate void SayHello();
        static void Main(string[] args)
        {
            int i = 0;
            if (true)
            {
                Console.WriteLine(i);
                Console.WriteLine("i = " + j);
                Console.WriteLine("i = " + i);
            }

            MyDelegate d1 = delegate()
            {
                i++;
                j++;
            }
            ;
            d1(); // obe +1

            DoIt(d1); // obe +1, ikdyz metody DoIt zdanlive nema pristup na lokalni promennou i
            Console.WriteLine("i = " + i);
            Console.WriteLine("i = " + j);

            Console.WriteLine("Example:");
            List<SayHello> pole = new List<SayHello>();
            for (int k = 1; k <= 100; k++)
            {
                var k1 = k;
                SayHello temp = delegate()
                {
                    Console.WriteLine("Hello " + k1);                    ;
                };
                pole.Add(temp);                                          
            }
            var sayHello = pole[9];
            sayHello();
        }

        static void DoIt(MyDelegate d)
        {
            d();            
        }
    }
}
