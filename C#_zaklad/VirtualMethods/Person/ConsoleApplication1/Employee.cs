using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Properties
{
    class Employee: Person
    {
        public string LastName
        {
            get { return base.LastName.ToUpper(); }
            set {}
        }
    }
}
