using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using lab1.Helpers;

namespace lab1.Model
{
    public class Calculator
    {
        public Memory _memory;

        public Calculator(Memory memory)
        {
            FirstNumber = "0";
            SecondNumber = string.Empty;
            Output = string.Empty;

            _memory = memory;
        }

        public event Action<string> OutputChanged;
        public event Action<string> EntryChanged;

        #region Properties

        private string _firstNumber;
        public string FirstNumber
        {
            get { return _firstNumber; }
            private set { _firstNumber = CalculatorHelper.FormatNumber(value); }
        }
        public bool HasFirstNumber => !string.IsNullOrEmpty(FirstNumber);


        private string _secondNumber;
        public string SecondNumber
        {
            get { return _secondNumber; }
            private set { _secondNumber = CalculatorHelper.FormatNumber(value); }
        }
        public bool HasSecondNumber => !string.IsNullOrEmpty(SecondNumber);


        public string Operation { get; private set; } = string.Empty;
        public bool HasOperation => !string.IsNullOrEmpty(Operation);


        public string PreviousSecondNumber { get; private set; } = string.Empty;
        public bool HasPreviousSecondNumber => !string.IsNullOrEmpty(PreviousSecondNumber);


        public string PreviousOperation { get; private set; } = string.Empty;
        public bool HasPreviousOperation => !string.IsNullOrEmpty(PreviousOperation);


        private string _output = string.Empty;
        public string Output
        {
            get
            {
                return _output;
            }
            private set
            {
                _output = value;
                OutputChanged?.Invoke(_output);
            }
        }


        private string _entry = "0";
        public string Entry
        {
            get
            {
                return _entry;
            }
            private set
            {
                _entry = CalculatorHelper.FormatNumber(value, userInput: true);
                EntryChanged?.Invoke(_entry);
            }
        }

        public bool IsMemoryEmpty => _memory.IsEmpty;
        #endregion

        #region Operations
        public void NumberEntered(string number)
        { 
            if (HasOperation)
            {
                SecondNumber = number;
            }
            else
            {
                FirstNumber = number;
            }
            Entry = number;
        }
        public void OperationEntered(string operation)
        {
            if (Entry.EndsWith("."))
            {
                Entry = Entry.Substring(0, Entry.Length - 1);
            }

            // Has first, second and operation.
            if (HasSecondNumber && HasOperation)
            {
                string result = CalculatorHelper.Execute(FirstNumber, SecondNumber, Operation);
                Output = result + " " + operation + " ";
                Entry = result.ToString();

                FirstNumber = Entry;
                SecondNumber = string.Empty;
            }
            // Has first.
            // Doesn't have second and operation.
            else
            {
                Output = FirstNumber + " " + operation + " ";
            }

            Operation = operation;
        }
        public void Execute()
        {
            // Has first, second and operation.
            if (HasSecondNumber && HasOperation)
            {
                Output = FirstNumber + " " + Operation + " " + SecondNumber + " = ";
                string result = CalculatorHelper.Execute(FirstNumber, SecondNumber, Operation);
                Entry = result;

                PreviousSecondNumber = SecondNumber;
                PreviousOperation = Operation;

                FirstNumber = Entry;
                SecondNumber = string.Empty;
                Operation = string.Empty;
            }
            // Has first and operation.
            else if (HasOperation)
            {
                SecondNumber = FirstNumber;
                Execute();
            }
            // Has first, doesn't has second and operation.
            // Has prevOperation and prevSecond.
            else if (HasPreviousOperation && HasPreviousSecondNumber)
            {
                SecondNumber = PreviousSecondNumber;
                Operation = PreviousOperation;
                Execute();
            }
            // Has first, doesn't has second and operation.
            // Doesn't have prevOperation and prevSecond.
            else
            {
                Output = FirstNumber + " = ";
                Entry = FirstNumber;
            }
        }
        public void Cancel()
        {
            Output = string.Empty;
            Entry = "0";

            FirstNumber = "0";
            SecondNumber = string.Empty;
            Operation = string.Empty;

            PreviousSecondNumber = string.Empty;
            PreviousOperation = string.Empty;

        }
        public void ClearEntry()
        {
            if (HasOperation)
            {
                Entry = "0";
                SecondNumber = "0";
            }
            else if (HasPreviousSecondNumber && HasPreviousOperation)
            {
                Output = string.Empty;
                Entry = "0";
                FirstNumber = "0";
            }
            else
            {
                Entry = "0";
                FirstNumber = "0";
            }
        }
        public void Backspace()
        {
            if ((HasOperation && HasSecondNumber) ||
                !(HasPreviousSecondNumber && HasPreviousOperation))
            {
                Entry = Entry.Substring(0, Entry.Length - 1);
                if (Entry == "")
                {
                    Entry = "0";
                }
                NumberEntered(Entry);
            }
            else if (HasPreviousSecondNumber && HasPreviousOperation)
            {
                Output = string.Empty;
            }
        }
        public void PlusMinus()
        {
            if (Entry.StartsWith("-"))
            {
                Entry = Entry.Substring(1, Entry.Length - 1);
            }
            else
            {
                Entry = "-" + Entry;
            }
            
            if (HasOperation)
            {
                SecondNumber = Entry;
            }
            else
            {
                FirstNumber = Entry;
            }
        }
        public void Module()
        {
            if (Entry.StartsWith("-"))
            {
                PlusMinus();
            }
        }
        public void Square()
        {
            if (!HasSecondNumber)
            {
                SecondNumber = FirstNumber;
            }

            

            string result = string.Empty;

            if (HasOperation)
            {
                Output = $"{FirstNumber} {Operation} sqr({SecondNumber}) =";
                result = CalculatorHelper.Execute(FirstNumber, CalculatorHelper.Execute(SecondNumber, SecondNumber, "×"), Operation);
                
                PreviousOperation = Operation;
                PreviousSecondNumber = CalculatorHelper.Execute(SecondNumber, SecondNumber, "×");
            }
            else
            {
                Output = $"sqr({FirstNumber}) = ";
                result = CalculatorHelper.Execute(FirstNumber, FirstNumber, "×");

               // PreviousOperation = "×";
            }

            Entry = result;
            FirstNumber = result;
            Operation = string.Empty;
            SecondNumber = string.Empty;
        }
        public void BackOperation()
        {
            if (!HasSecondNumber)
            {
                SecondNumber = FirstNumber;
            }

            string result = string.Empty;

            if (HasOperation)
            {
                Output = $"{FirstNumber} {Operation} 1/({SecondNumber}) = ";
                result = CalculatorHelper.Execute(FirstNumber, CalculatorHelper.Execute("1", SecondNumber, "÷"), Operation);

                PreviousOperation = Operation;
                PreviousSecondNumber = CalculatorHelper.Execute("1", SecondNumber, "÷");
            }
            else
            {
                Output = $"1/({FirstNumber}) = ";
                result = CalculatorHelper.Execute("1", FirstNumber, "÷");

              //  PreviousOperation = "÷"; 
            }

            Entry = result;
            FirstNumber = result;
            Operation = string.Empty;
            SecondNumber = string.Empty;
        }
        public void SquareRoot()
        {
            if (!HasSecondNumber)
            {
                SecondNumber = FirstNumber;
            }

            string result = string.Empty;

            if (HasOperation)
            {
                Output = $"{FirstNumber} {Operation} √({SecondNumber}) = ";
                result = CalculatorHelper.Execute(FirstNumber, CalculatorHelper.ExecuteSquareRoot(SecondNumber), Operation);

                PreviousOperation = Operation;
                PreviousSecondNumber = CalculatorHelper.ExecuteSquareRoot(SecondNumber);
            }
            else
            {
                Output = $"√({FirstNumber}) = ";
                result = CalculatorHelper.ExecuteSquareRoot(FirstNumber);

               // PreviousOperation = "√"; 
            }

            Entry = result;
            FirstNumber = result;
            Operation = string.Empty;
            SecondNumber = string.Empty;
        }
        public void Percent()
        {
            if (!HasSecondNumber)
            {
                SecondNumber = FirstNumber;
            }

            string result = string.Empty;

            if (HasOperation)
            {
                string calculatedSecond = CalculatorHelper.ExecutePercent(FirstNumber, SecondNumber);

                Output = $"{FirstNumber} {Operation} {calculatedSecond} = ";
                result = CalculatorHelper.Execute(FirstNumber, calculatedSecond, Operation);

                PreviousOperation = Operation;
                PreviousSecondNumber = calculatedSecond;
            }
            else
            {
                result = CalculatorHelper.DecimalToPercent(FirstNumber);
                Output = $"{FirstNumber} / 100 = ";

                PreviousOperation = "÷";
                PreviousSecondNumber = "100";
            }

            Entry = result;
            FirstNumber = result;
            Operation = string.Empty;
            SecondNumber = string.Empty;
        }

        public void MemoryClear()
        {
            _memory.Clear();
        }

        public void MemoryRead()
        {
            Entry = _memory.Value;
            if (HasOperation)
            {
                SecondNumber = Entry;
            }
            else
            {
                FirstNumber = Entry;
            }
        }

        #endregion

        #region MemoryOperations
        public void MemoryPlus()
        {
            _memory.Plus(Entry);
        }

        public void MemoryMinus()
        {
            _memory.Minus(Entry);
        }

        public void MemorySave()
        {
            _memory.Save(Entry);
        }
        #endregion
    }
}
