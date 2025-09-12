using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _01_UsingDelegates
{
    class Program
    {
        delegate int MyDelegate(int a, int b);
        static void Main(string[] args)
        {
            int sum;
            //sum = Sum(10, 20);
            //Console.WriteLine(sum);

            MyDelegate d1 = Sum;
            MyDelegate d2 = Max;
            //d1 = (MyDelegate)MyDelegate.Combine(d1, d2); //invocation list , do D1 pridam odkaz na metodu D1 i D2            
            d1 +=d2; 
                     
            sum = d1(10, 20);
            Console.WriteLine(sum);
        }

        private static int Max(int a, int b)
        {
            Console.WriteLine("Max...");
            return (a > b) ? a : b;
        }

        private static int Sum(int a, int b)
        {
            Console.WriteLine("Sum...");
            return a + b;
        }
    }
}
