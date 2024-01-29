using System.Globalization;

namespace Lab1;


public class Program
{
    static void Main()
    {
        BinaryNumber a = new();
        BinaryNumber b = new();

        try
        {
            Console.WriteLine("Choose format of numbers: b - binary, d - decimal");
            Console.Write("Format: ");
            string? format = Console.ReadLine();

            Converter converter = format switch
            {
                "b" => MyConverter.BinaryStringToDigits,
                "d" => MyConverter.DecimalStringToDigits,
                _ => throw new FormatException("Invalid format.")
            };

            string formatString = format switch
            {
                "b" => "binary",
                "d" => "decimal",
                _ => throw new FormatException("Invalid format.")
            };

            Console.WriteLine($"\nEnter two {Constants.BinaryNumberLength}-bit {formatString} numbers:");

            Console.Write("a = ");
            a = new(Console.ReadLine(), converter);

            Console.Write("b = ");
            b = new(Console.ReadLine(), converter);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
            return;
        }

        Console.WriteLine($"\na = {a.ToStraight()}");
        Console.WriteLine($"a = {a.ToAdditional()}");
        Console.WriteLine($"a = {a.ToDecimal()}");
        Console.WriteLine($"\nb = {b.ToStraight()}");
        Console.WriteLine($"b = {b.ToAdditional()}");
        Console.WriteLine($"b = {b.ToDecimal()}\n");

        try
        {
            var plusResult = a + b;
            Console.WriteLine($"a + b = {plusResult.ToStraight()}");
            Console.WriteLine($"a + b = {plusResult.ToAdditional()}");
            Console.WriteLine($"a + b = {plusResult.ToDecimal()}\n");

            var minusResult = a - b;
            Console.WriteLine($"a - b = {minusResult.ToStraight()}");
            Console.WriteLine($"a - b = {minusResult.ToAdditional()}");
            Console.WriteLine($"a - b = {minusResult.ToDecimal()}\n");

            var multiplyResult = a * b;
            Console.WriteLine($"a * b = {multiplyResult.ToStraight()}");
            Console.WriteLine($"a * b = {multiplyResult.ToAdditional()}");
            Console.WriteLine($"a * b = {multiplyResult.ToDecimal()}\n");

            (var quotient, var remainder) = a.ToExpandedBitGrid() / b;
            Console.WriteLine($"a / b = {quotient.ToStraight()}   ({remainder.ToStraight()})");
            Console.WriteLine($"a / b = {quotient.ToAdditional()} ({remainder.ToAdditional()})");
            Console.WriteLine($"a / b = {quotient.ToDecimal()} ({remainder.ToDecimal()})");
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
            return;
        }
    }
}

