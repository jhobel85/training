#define POKUS
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace _01_PreprocessorDirectives
{



    class Program
    {


        static void Main(string[] args)
        {
#if DEBUG
            Console.WriteLine("In Debug");
#endif


#if Release
            Console.WriteLine("In Release");
#endif

#if POKUS
            Console.WriteLine("In Pokus");
#endif
        }

    }
}

