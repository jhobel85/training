using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Auto
    {
        private int cena;
        public static int ID_AUTA_LAST;
        private int IDAuta;

        public Auto(int cena)
        {
            IDAuta = ++ID_AUTA_LAST;
            if (cena < 0)
            {
                throw new Exception("Cena je zaporna.");
            }
        }

        public int getIDAuta()
        {
            return IDAuta;
        }

    }
}
