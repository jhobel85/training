using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Finalizing
{
    class Program
    {
        static void Main(string[] args)
        {
            FileStream fileStream = new FileStream();

            try
            {

                fileStream.Open();
                //do something
                throw new Exception("Invalid FileStream operation");
            }
            
            catch (Exception e)
            {
                Console.WriteLine("EEEE");
                Console.WriteLine(e.StackTrace);
            }            
            finally { 
                if (fileStream != null) { fileStream.Close(); }            
            }                        
        }
    }
}
