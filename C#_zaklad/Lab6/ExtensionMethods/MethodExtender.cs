using System;

namespace AnotherNamespace
{
    public static class MethodExtender
    {
        //definive promenne sentence pres kterou pristupuji do stringu
        public static string ToSentence(this string sentence, bool makeDot)
        {
            sentence = sentence[0].ToString().ToUpper() + sentence.Substring(1);
            if (makeDot && sentence[sentence.Length - 1] != '.')
            {
                sentence += ".";
            }
            return sentence;
        }
    }
}