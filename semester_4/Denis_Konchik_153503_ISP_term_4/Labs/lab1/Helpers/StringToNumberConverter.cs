using Android.Icu.Util;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1.Helpers
{
    public class StringToNumberConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var cult = new CultureInfo("ru-RU") 
            { 
                NumberFormat = { NumberGroupSeparator = "."}
            };

            return (string)parameter + ((int?)value)?.ToString("#,#", cult);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
