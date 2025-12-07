using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _03_OptionalParameters
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(Calculate(10,20,30,40));
            Console.WriteLine(Calculate(a:10, b:20, c:30, d:40));
            Console.WriteLine(Calculate(d: 10, c: 20, a: 30, b: 40));
            Console.WriteLine(Calculate(10, d: 40));
        }

        static int Calculate(int a, int b, int c, int d)
        {
            return a + b - c - d;
        }

        // parametry a - e je nepovinny
        static int Calculate(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0)
        {
            return a + b - c - d + d;
        }
    }
}
