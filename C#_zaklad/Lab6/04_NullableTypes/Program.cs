using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _04_NullableTypes
{
    class Program
    {
        static void Main(string[] args)
        {
            int? i = null;
            i = i + 1;
            if (i.HasValue) { 
            Console.WriteLine("Nullable:" + i.Value);
            }

            i = i.GetValueOrDefault() + 1;
            Console.WriteLine("Value:" + i); //1

            i = null;
            i = i.GetValueOrDefault(1) + 1;
            Console.WriteLine("Value:" + i); //2

            int? j = null;
            j = (j ?? 1) + 1;
            Console.WriteLine("Value:" + j); //2

            StringBuilder sb = MakeStringBuilder("");
            int? length = sb?.Length; //nevyhod vyjmku v pripade sb bude null.
            Console.WriteLine("Pocet znaku:" + + (length??0));//zapis 0 v pripade null

            string[] list = null;
            Console.WriteLine("List lenght:" + (list?[0]?.Length ?? 0));
        }

        static StringBuilder MakeStringBuilder(string s)
        {
            
            if (!string.IsNullOrEmpty(s))
            {
                return new StringBuilder(s);
            }
            return null;
                        
        }
    }
}
