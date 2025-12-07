using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _04_01_OperatorOverloading
{
    class Date
    {
        public int Year, Month, Day;

        public Date(int day, int month, int year)
        {
            this.Day = day;
            this.Month = month;
            this.Year = year;
        }

        public override string ToString()
        {
            return string.Format("{0:D2}.{1:D2}.{2:D4}", this.Day, this.Month, this.Year);
        }

        public Date AddDays(int dayCount)
        {
            this.Day += dayCount;
            return this;
        }

        public override int GetHashCode()
        {
            return this.ToString().GetHashCode();
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
            {
                return false;
            }
            Date date = (Date) obj;
            
            return (date.Day == this.Day && date.Month == this.Month && date.Year == this.Year);
        }

        public static Date operator +(Date dat, int dayCount)
        {
            return new Date(dat.Day + dayCount, dat.Month, dat.Year);
        }

        public static Date operator ++(Date dat)
        {
            return new Date(dat.Day + 1, dat.Month, dat.Year);
        }

        public static bool operator ==(Date d1, Date d2)
        {
            return d1 != null && d2 != null && d1.Equals(d2);
        }

        public static bool operator !=(Date d1, Date d2)
        {            
            return !d1.Equals(d2);
        }
    }
}
