using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _04_01_OperatorOverloading
{
    class Program
    {
        static void Main(string[] args)
        {
            Date d1 = new Date(1,1,2014);
            //d1.AddDays(14);
            d1 += 14;
            d1++;
            Console.WriteLine(d1.ToString());            
            Date d2 = new Date(8, 8, 2014);
            Date d3 = new Date(8, 8, 2014);
            Console.WriteLine(d2 == d3);
        }
    }
}
