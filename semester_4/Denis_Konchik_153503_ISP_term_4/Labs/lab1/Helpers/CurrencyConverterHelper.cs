namespace lab1.Helpers;

public class CurrencyConverterHelper
{
    public static decimal StringToDecimal(string str)
    {
        if (str is null)
        {
            return 0;
        }

        if (str.StartsWith("."))
        {
            str = "0" + str;
        }
        else if (str == "")
        {
            str = "0";
        }

        return Convert.ToDecimal(str);
    }

    public static string DecimalToString(decimal number)
    {
        if (number == 0)
        {
            return "0";
        } 
        else
        {
            return number.ToString();
        }
    }
}
