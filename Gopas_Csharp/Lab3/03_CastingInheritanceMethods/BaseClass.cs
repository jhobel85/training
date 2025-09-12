using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _03_CastingInheritanceMethods
{
    class BaseClass<T> where T : IComparable, new()
    {
        public virtual T SomeMethod()
        {
            return new T();
        }
    }
}
