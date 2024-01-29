using System.Numerics;

namespace Lab1;


public class BinaryNumber : ICloneable
{
    private int[] _bits;

    public BinaryNumberState State { get; private set; }

    public int Length => _bits.Length;

    public BinaryNumber(int numberLength = Constants.BinaryNumberLength)
    {
        State = BinaryNumberState.Straight;
        _bits = new int[numberLength];
    }

    public BinaryNumber(string? number, Converter converter, int numberLength = Constants.BinaryNumberLength)
        : this(numberLength)
    {
        _bits = converter(number, numberLength);
    }

    public BigInteger ToDecimal()
    {
        BinaryNumber tempNumber = this.ToStraight();

        BigInteger dec = 0;

        for (int i = 0; i < tempNumber._bits.Length - 1; i++)
        {
            BigInteger pow2 = i switch
            {
                0 => 1,
                _ => (BigInteger)2 << (i - 1)
            };

            dec += tempNumber._bits[i] * pow2;
        }

        if (tempNumber._bits.Last() == 1)
        {
            dec = -dec;
        }

        return dec;
    }

    private static int[] Negation(int[] digits, int length)
    {
        for (int i = 0; i < length; i++)
        {
            digits[i] ^= 1;
        }

        int transfer = 1;
        for (int i = 0; i < length; i++)
        {
            digits[i] = digits[i] + transfer;
            transfer = digits[i] / 2;
            digits[i] %= 2;
        }

        return digits;
    }

    private static BinaryNumber _numberWithCertainState(BinaryNumber number, BinaryNumberState state)
    {
        return number.State switch
        {
            BinaryNumberState.Straight => number.ToStraight(),
            BinaryNumberState.Additional => number.ToAdditional(),
            _ => throw new InvalidOperationException()
        };
    }

    public BinaryNumber ToNegative()
    {
        BinaryNumber result = ((BinaryNumber)this.Clone()).ToAdditional();
        result._bits = Negation(result._bits, result._bits.Length);

        return _numberWithCertainState(result, this.State);
    }

    public BinaryNumber ToAdditional()
    {
        var result = (BinaryNumber)this.Clone();

        if (!(State == BinaryNumberState.Additional ||
            _bits.Last() == 0))
        {
            result._bits = Negation((int[])_bits.Clone(), _bits.Length - 1);
        }

        result.State = BinaryNumberState.Additional;
        return result;
    }

    public BinaryNumber ToStraight()
    {
        var result = (BinaryNumber)this.Clone();

        if (!(State == BinaryNumberState.Straight ||
            _bits.Last() == 0))
        {
            result._bits = Negation((int[])_bits.Clone(), _bits.Length - 1);
        }

        result.State = BinaryNumberState.Straight;

        return result;
    }

    public BinaryNumber ToExpandedBitGrid()
    {
        var result = (BinaryNumber)this.Clone();

        int[] additionalArray = new int[result.Length];

        if (result._bits.Last() == 1)
        {
            if (result.State == BinaryNumberState.Straight)
            {
                result._bits[result.Length - 1] = 0;
                additionalArray[additionalArray.Length - 1] = 1;
            }
            else if (result.State == BinaryNumberState.Additional)
            {
                for (int i = 0; i < additionalArray.Length; i++)
                {
                    additionalArray[i] = 1;
                }
            }
            else
            {
                throw new InvalidDataException();
            }
        }

        result._bits = result._bits.Concat(additionalArray).ToArray();

        return result;
    }

    public override string? ToString()
    {
        return String.Concat(_bits.Reverse()) + $" [{MyConverter.StateToString(State)}]";
    }

    public object Clone()
    {
        return new BinaryNumber()
        {
            _bits = (int[])this._bits.Clone(),
            State = this.State
        };
    }

    public static BinaryNumber operator +(BinaryNumber a, BinaryNumber b)
    {
        BinaryNumber result = new() { State = BinaryNumberState.Additional };
        a = a.ToAdditional();
        b = b.ToAdditional();

        int transfer = 0;
        for (int i = 0; i < result._bits.Length; i++)
        {
            result._bits[i] = a._bits[i] + b._bits[i] + transfer;
            transfer = result._bits[i] / 2;
            result._bits[i] %= 2;
        }



        if (a._bits.Last() == b._bits.Last() &&
            result._bits.Last() != a._bits.Last())
        {
            throw new OverflowException("Overflow in \"+\" operaion.");
        }

        return result;
    }

    public static BinaryNumber operator -(BinaryNumber a, BinaryNumber b)
    {
        try
        {
            return a.ToAdditional() + b.ToNegative().ToAdditional();
        }
        catch
        {
            throw new OverflowException("Overflow in \"-\" operaion.");
        }
    }

    public static BinaryNumber operator *(BinaryNumber a, BinaryNumber b)
    {
        if (a.Length != b.Length)
        {
            throw new NotImplementedException();
        }

        var M = a.ToAdditional(); // Множимое
        var Q = b.ToAdditional(); // Множитель
        var A = new BinaryNumber();
        int Q_1 = 0;

        int Count = a.Length;

        while (Count != 0)
        {
            if (Q._bits[0] == 1 && Q_1 == 0)
            {
                A -= M;
            }
            else if (Q._bits[0] == 0 && Q_1 == 1)
            {
                A += M;
            }

            Q_1 = Q._bits[0];

            for (int i = 0; i < Q.Length - 1; i++)
            {
                Q._bits[i] = Q._bits[i + 1];
            }

            Q._bits[Q.Length - 1] = A._bits[0];

            for (int i = 0; i < A.Length - 1; i++)
            {
                A._bits[i] = A._bits[i + 1];
            }

            Count--;
        }

        return new BinaryNumber()
        {
            State = BinaryNumberState.Additional,
            _bits = Q._bits.Concat(A._bits).ToArray()
        };

    }

    public static (BinaryNumber, BinaryNumber) operator /(BinaryNumber a, BinaryNumber b)
    {
        if (a.Length != 2 * b.Length)
        {
            throw new InvalidDataException();
        }

        // 1.
        a = a.ToAdditional();
        b = b.ToAdditional();

        // A..Q - делимое

        var A = new BinaryNumber(b.Length).ToAdditional(); // Остаток
        A._bits = a._bits[b.Length..];

        var Q = new BinaryNumber(b.Length).ToAdditional(); // Частное
        Q._bits = a._bits[..b.Length];

        var M = b.ToAdditional(); // Делитель
        int Count = Q.Length;

        while (Count != 0)
        {
            // 2.
            for (int i = A._bits.Length - 1; i > 0; i--)
            {
                A._bits[i] = A._bits[i - 1];
            }

            A._bits[0] = Q._bits.Last();

            for (int i = Q._bits.Length - 1; i > 0; i--)
            {
                Q._bits[i] = Q._bits[i - 1];
            }

            Q._bits[0] = 0;

            // 3.
            var A_backup = (BinaryNumber)A.Clone();

            if (M._bits.Last() == A._bits.Last())
            {
                A -= M; 
            }
            else
            {
                A += M;
            }

            // 4.
            if (A_backup._bits.Last() == A._bits.Last() ||
                (A._bits.Sum() + Q._bits.Sum() == 0))
            {
                Q._bits[0] = 1;
            }
            else if (A_backup._bits.Last() != A._bits.Last() &&
                (A._bits.Sum() + Q._bits.Sum() != 0))
            {
                Q._bits[0] = 0;
                A = A_backup;
            }

            Count--;
        }

        // 6.
        if (a._bits.Last() != b._bits.Last())
        {
            Q = Q.ToNegative();
        }

        return (Q, A);
    }
}
