using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace DelegateCallBack
{
    public delegate void WorkCompletedCallBack(string result);

    class Program
    {
        

        static void Main(string[] args)
        {
            Helper.CallBack = CallBackFunction;
            Helper.DoWork();            
        }

        private static void CallBackFunction(string result)
        {
            Console.WriteLine(result);
        }
    }
}
