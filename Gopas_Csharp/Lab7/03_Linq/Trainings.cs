using System.Collections;
using System.Collections.Generic;

namespace _03_Linq
{
    public class Trainings : IEnumerable
    {
        Training[] trainings =
        {
            new Training("C#"), new Training("ASP.NET Web Forms"), new Training("ASP.NET MVC"),
            new Training("JavaScript")
        };

        public IEnumerator GetEnumerator()
        {
            return new TrainingEnumerator(this.trainings);
        }
    }
}