using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Properties
{
    class AutomaticProperties
    {
        static void Main(string[] args)
        {
            Person per = new Person();
            per.FirstName = "Josef";
            Console.WriteLine(per.FirstName);

        }
    }
}
