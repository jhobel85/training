using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Collections
{
   

    class TrainingEnumerator: IEnumerator
    {
        int index = -1;
        Training[] trainings;

        public TrainingEnumerator(Training[] trainings)
        {
            this.trainings = trainings;
        }

        public bool MoveNext()
        {
            this.index++;
            if (this.index >= this.trainings.Length)
            {
                return false;
            }
            return true;
        }

        public void Reset()
        {
            this.index = -1;
        }

        public object Current
        {
            get { return this.trainings[this.index]; } 
        }
    }
}
