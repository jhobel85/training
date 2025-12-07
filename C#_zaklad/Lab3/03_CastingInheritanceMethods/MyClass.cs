using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _03_CastingInheritanceMethods
{
    class MyClass<T>: BaseClass<T> where T : IComparable, new()
    {
        public override T SomeMethod()
        {
            return new T();
        }

        public void MyMethod<K>(K k) where K:class // omezeni na referencni parametr
        {
            // je treba tady pouzit jiny parametr nez T, aby se to nematlo s gen. parametrem T ve tride.
            MyClass<int> obj = new MyClass<int>();
            obj.MyMethod<Object>(3);
        }
    }
}
