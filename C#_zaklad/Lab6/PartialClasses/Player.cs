using System;

namespace PartialClasses
{
    partial class Player: IPlayable
    {
        public void Play()
        {
            onPlayBegin();
            onPlayEnd();
        }

        public void Stop()
        {
            
        }

        partial void onPlayBegin();
        partial void onPlayEnd();
    }

    partial class Player
    {
        partial void onPlayBegin()
        {
            Console.WriteLine("Play Begin");
        }

        partial void onPlayEnd()
        {
            Console.WriteLine("Play End");
        }
    }
}