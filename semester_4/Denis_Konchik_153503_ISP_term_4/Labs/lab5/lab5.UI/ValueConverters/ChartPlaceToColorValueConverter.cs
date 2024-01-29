using lab5.Domain.Entities;
using System.Globalization;

namespace lab5.UI.ValueConverters;

public class ChartPlaceToColorValueConverter : IValueConverter
{
    public Color DefaultBackgroundColor { get; set; } = Colors.White;
    public Color WrongBackgroundColor { get; set; } = Colors.White;

    public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
    {
        if (value is int chartPlace)
        {
            return chartPlace switch
            {
                > 500 => WrongBackgroundColor,
                _ => DefaultBackgroundColor
            };
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
