using System.Collections;

namespace Collections
{
    class Trainings : IEnumerable
    {
        Training[] trainings =
        {
            new Training("C#"), new Training("ASP.NET"), new Training("ASP.NET MVC"),
            new Training("JavaScript")
        };

        public IEnumerator GetEnumerator()
        {
            return new TrainingEnumerator(this.trainings);
        }
    }
}
