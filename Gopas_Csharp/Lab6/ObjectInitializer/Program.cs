using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectInitializer
{
    class Program
    {
        static void Main(string[] args)
        {
            
            Employee e = new Employee(1);            
            e.FirstName = "Karel";
            e.LastName = "Novak";
            Console.WriteLine(e.ToString());
            
            Employee e2 = new Employee(2)
            {
                FirstName = "Karel",
                LastName = "Novak"
        };

            Employee e3 = new Employee(3) {FirstName = "Karel", LastName = "Novak"};

            Employee e4 = new Employee(4) { FirstName = "Karel"};
        }
    }
}
