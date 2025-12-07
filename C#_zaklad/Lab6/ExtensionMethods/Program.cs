using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AnotherNamespace;

namespace ExtensionMethods
{
    class Program
    {
        static void Main(string[] args)
        {            
            string sentence = "ahoj, podej mi prosim lzici";
            Console.WriteLine("The sentence is: {0}",sentence);

            
            Console.WriteLine("Fixed sentence is: {0}", sentence.ToSentence(false));
        }

        
    }
}
