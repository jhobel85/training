using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;

namespace VirtualMethods
{
    class Cat : Animal
    {
        public string Sound()
        {
            return "Miau";
        }
    }
}
