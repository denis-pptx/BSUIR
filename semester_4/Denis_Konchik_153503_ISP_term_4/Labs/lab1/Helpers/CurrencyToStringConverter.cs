using lab1.Entities;
using System.Globalization;

namespace lab1.Helpers;

public class CurrencyToStringConverter : IValueConverter
{
    public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
    {
        if (value is Currency currency)
        {
            string emoji = currency.Cur_Abbreviation switch
            {
                "BYN" => "🇧🇾",
                "RUB" => "🇷🇺",
                "EUR" => "🇪🇺",
                "USD" => "🇺🇸",
                "CHF" => "🇨🇭",
                "CNY" => "🇨🇳",
                "GBP" => "🇬🇧",
                _ => "❓"
            };

            return currency.Cur_Abbreviation + " " + emoji;
        }
        else
        {
            throw new NotImplementedException();
        }
    }

    public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
    {
        throw new NotImplementedException();
    }
}
