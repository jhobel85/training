using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VirtualMethods
{
    class Animal
    {
        new public string sound()
        {
            return "generic sound";
        }
    }
}
