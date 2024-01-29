using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using lab1.Settings;

namespace lab1.Helpers
{
    public static class CalculatorHelper
    {
        
        public static string Execute(string _firstNumber, string _secondNumber, string operation)
        {
            Double result = 0;
            Double firstNumber = Convert.ToDouble(_firstNumber.Replace(" ", ""), new CultureInfo("en-US"));
            Double secondNumber = Convert.ToDouble(_secondNumber.Replace(" ", ""), new CultureInfo("en-US"));

            switch(operation)
            {
                case "+":
                    result = firstNumber + secondNumber;
                    break;
                case "-":
                    result = firstNumber - secondNumber;
                    break;
                case "×":
                    result = firstNumber * secondNumber;
                    break;
                case "÷":
                    result = firstNumber / secondNumber;
                    break;
                default:
                    throw new InvalidOperationException();
            }
            return FormatNumber(result);
        }

        public static string ExecuteSquareRoot(string _number)
        {
            Double number = Convert.ToDouble(_number.Replace(" ", ""), new CultureInfo("en-US"));
            Double result = Math.Sqrt(number);

            return FormatNumber(result);
        }

        public static string ExecutePercent(string _number, string _percent)
        {
            Double number = Convert.ToDouble(_number.Replace(" ", ""), new CultureInfo("en-US"));
            Double percent = Convert.ToDouble(_percent.Replace(" ", ""), new CultureInfo("en-US"));
            Double result = number * percent / 100;

            return FormatNumber(result);
        }

        public static string DecimalToPercent(string _number)
        {
            Double number = Convert.ToDouble(_number.Replace(" ", ""), new CultureInfo("en-US"));
            Double percent = number / 100;

            return FormatNumber(percent);
        }
        private static string InsertSpaces(this string str, int pos)
        {
            int mantissaLength = str.IndexOf('.');
            if (mantissaLength == -1)
            {
                mantissaLength = str.Length;
            }

            for (int i = mantissaLength - pos; i > 0; i -= pos)
            {
                str = str.Insert(i, " ");
            }

            str = str.Replace("- ", "-").Replace(" -", "-").Replace(" +", "+").Replace("+ ", "+");
            return str;
        }
        public static string FormatNumber(Double value, bool userInput = false)
        {
            return FormatNumber(value.ToString().Replace(",", "."), userInput);
        }

        public static string FormatNumber(string value, bool userInput = false)
        {
            if (string.IsNullOrEmpty(value))
            {
                return value;
            }

            if (value == ".")
            {
                value = "0.";
            }
            else if (value == "-")
            {
                value = "0";
            }

            value = value.Replace(" ", "");

            if (userInput == true)
            {
                value = value.InsertSpaces(3);
            }
            else
            {
                if (Decimal.TryParse(value, new CultureInfo("en-US"), out Decimal valueDecimal))
                {
                    value = valueDecimal.ToString($"G{TextSettings.MaxDigitsInEntryNumber}").
                        Replace(",", ".").InsertSpaces(3);
                }
                else if (Double.TryParse(value, new CultureInfo("en-US"), out Double valueDouble))
                {
                    value = valueDouble.ToString($"G{TextSettings.MaxDigitsInEntryNumber}").
                        Replace(",", ".").InsertSpaces(3);
                }
                else
                {
                    value = "0";
                }
            }

            if (value == "-0")
            {
                value = "0";
            }

            return value;

        }
    }
}
