using System.Collections;

namespace _03_Linq
{
    public class TrainingEnumerator: IEnumerator
    {
        private int index = -1;
        private Training[] trainings;

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