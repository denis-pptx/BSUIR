using System.Numerics;

namespace Lab1;


public delegate int[] Converter(string? input, int numberLength);

public class MyConverter
{
    public static string StateToString(BinaryNumberState state)
    {
        return state switch
        {
            BinaryNumberState.Straight => "Straight code",
            BinaryNumberState.Additional => "Additional code",
            _ => throw new InvalidDataException($"Invalid {nameof(BinaryNumberState)}")
        };
    }
    public static int[] BinaryStringToDigits(string? input, int numberLength)
    {
        if (input == null)
        {
            throw new ArgumentNullException("Incorrect input: null");
        }

        if (numberLength < 0)
        {
            throw new ArgumentOutOfRangeException();
        }


        foreach (var digit in input)
        {
            if (!(digit == '0' || digit == '1'))
            {
                throw new InvalidDataException("Incorrect input: enetered number must consist of only 0 and 1.");
            }
        }

        if (input.Length > numberLength)
        {
            throw new InvalidDataException("Incorrect input: entered number is too long.\n" +
                $"Max length: {numberLength}\n" +
                $"Your length: {input.Length}");
        }

        while(input.Length != numberLength)
        {
            input = input.Insert(0, "0");
        }

        return input.ToArray().Select(c => c - '0').Reverse().ToArray();
    }

    public static int[] DecimalStringToDigits(string? input, int numberLength)
    {
        if (input == null)
        {
            throw new ArgumentNullException("Incorrect input: null");
        }

        if (numberLength < 0)
        {
            throw new ArgumentOutOfRangeException();
        }

        BigInteger inputDecimal = BigInteger.Parse(input);
        if (!(inputDecimal <= (BigInteger)Math.Pow(2, numberLength - 1) - 1 && 
            inputDecimal >= -(BigInteger)Math.Pow(2, numberLength - 1) - 1)) {

            throw new InvalidDataException($"Entered number does not fit in {numberLength} bits.");
        }
        int[] result = new int[numberLength];

        if (inputDecimal < 0)
        {
            result[numberLength - 1] = 1;
            inputDecimal = -inputDecimal;
        }

        for (int i = 0; i < numberLength - 1 && inputDecimal != 0; i++)
        {
            result[i] = (int)(inputDecimal % 2);
            inputDecimal /= 2;
        }

        return result;

    }
}
