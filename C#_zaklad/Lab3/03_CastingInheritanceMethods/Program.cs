using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _03_CastingInheritanceMethods
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            string[] list = {"Praha", "Brno", "Ostrava", "Plzen", "Ceske Budejovice"};
            Array.Sort<String>(list);

            foreach (var item in list)
            {
                Console.WriteLine(item);                
            }

            Console.WriteLine(Array.IndexOf(list,"Praha"));
            Console.WriteLine(Array.BinarySearch(list, "Praha"));
        }
    }
}
