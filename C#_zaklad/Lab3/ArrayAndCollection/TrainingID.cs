using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArrayAndCollection
{
    class TrainingID
    {
        public string Prefix;
        public int Code;

        public TrainingID(string Prefix, int COde)
        {
            this.Prefix = Prefix;
            this.Code = COde;
        }

        
        public override bool Equals(object obj)
        {
            TrainingID t = obj as TrainingID;
            if (t == null) return false;

            if ((t.Prefix == this.Prefix) && (t.Code == this.Code))
            {
                return true;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return this.Prefix.GetHashCode() & this.Code.GetHashCode();
        }        
    }
}
