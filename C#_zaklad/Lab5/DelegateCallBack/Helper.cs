using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using DelegateCallBack;

namespace DelegateCallBack
{
    class Helper
    {
        public static WorkCompletedCallBack CallBack;

        public static void DoWork()
        {
            if (CallBack != null)
            {
                Console.WriteLine("Doing my work");
                CallBack(string.Format("{0} [{1}]", "Hello World", DateTime.Now.ToLongTimeString()));
            }            
        }
    }
}
