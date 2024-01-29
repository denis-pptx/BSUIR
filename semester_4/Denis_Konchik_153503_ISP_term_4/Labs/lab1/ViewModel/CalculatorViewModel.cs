using lab1.Helpers;
using lab1.Model;
using lab1.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace lab1.ViewModel
{
    public class CalculatorViewModel : BaseViewModel
    {
        private Calculator _calculator;
        public CalculatorViewModel(Calculator calculator)
        {
            _calculator = calculator;
            _calculator.OutputChanged += (output) => { Output = output; };
            _calculator.EntryChanged += (entry) => { Entry = entry; };

            #region Properties Initializing

            Entry = "0";
            Output = "";

            IsDigitButtonEnabled = true;
            IsSquareRootButtonEnabled = true;

            EntryLabelFontSize = TextSettings.EntryLabelDefaultFontSize;
            OutputLabelFontSize = TextSettings.OutputLabelDefaultFontSize;

            #endregion

            #region Commands Initializing

            DigitCommand = new Command<string>(digitCommand);
            CancelCommand = new Command(() =>
            {
                _calculator.Cancel();
                RefreshCanExecutes();
            });
            CleanEntryCommand = new Command(() =>
            {
                _calculator.ClearEntry();
                RefreshCanExecutes();
            });
            SimpleOperationCommand = new Command<string>((arg) =>
            {
                _calculator.OperationEntered(arg);
                IsDigitButtonEnabled = true;
            });
            EqualsCommand = new Command(() =>
            {
                _calculator.Execute();
                IsDigitButtonEnabled = true;
                ((Command)DotCommand).ChangeCanExecute();
            });
            DotCommand = new Command(
                execute: () =>
                {
                    digitCommand(".");
                    RefreshCanExecutes();
                },
                canExecute: () => !Entry.Contains(".") && (_entry.Replace(" ", "").Replace("-", "").Replace(".", "").Length
                    < TextSettings.MaxDigitsInEntryNumber));

            BackspaceCommand = new Command(
                execute: () =>
                {
                    _calculator.Backspace();
                    IsDigitButtonEnabled = true;
                    ((Command)BackspaceCommand).ChangeCanExecute();
                    ((Command)DotCommand).ChangeCanExecute();
                },
                canExecute: () => Entry.Length > 1 || Entry != "0");

            PlusMinusCommand = new Command(
                execute: () =>
                {
                    _calculator.PlusMinus();
                    //((Command)PlusMinusCommand).ChangeCanExecute();
                },
                canExecute: () => Entry != "0");
            ModuleCommand = new Command(() => _calculator.Module());
            SquareCommand = new Command(() =>
            {
                _calculator.Square();
                IsDigitButtonEnabled = true;
            });
            BackOperationCommand = new Command(() =>
            {
                _calculator.BackOperation();
                IsDigitButtonEnabled = true;
            });
            SquareRootCommand = new Command(() =>
            {
                _calculator.SquareRoot();
                IsDigitButtonEnabled = true;
            });
            PercentCommand = new Command(() =>
            {
                _calculator.Percent();
                IsDigitButtonEnabled = true;
            });


            MC_Command = new Command(
                execute: () =>
                {
                    _calculator.MemoryClear();
                    RefreshMemoryCanExecutes();
                },
                canExecute: () => !_calculator.IsMemoryEmpty);

            MR_Command = new Command(
                execute: () =>
                {
                    _calculator.MemoryRead();
                    RefreshMemoryCanExecutes();
                },
                canExecute: () => !_calculator.IsMemoryEmpty);

            MPlus_Command = new Command(
                execute: () =>
                {
                    _calculator.MemoryPlus();
                    RefreshMemoryCanExecutes();
                });

            MMinus_Command = new Command(
                execute: () =>
                {
                    _calculator.MemoryMinus();
                    RefreshMemoryCanExecutes();
                });
            MS_Command = new Command(
                execute: () =>
                {
                    _calculator.MemorySave();
                    RefreshMemoryCanExecutes();
                });

            #endregion
        }

        #region Properties

        private bool _isDigitButtonEnabled;
        public bool IsDigitButtonEnabled
        {
            get { return _isDigitButtonEnabled; }
            set { SetProperty(ref _isDigitButtonEnabled, value); }
        }

        private bool _isSquareRootButtonEnabled;
        public bool IsSquareRootButtonEnabled
        {
            get { return _isSquareRootButtonEnabled; }
            set { SetProperty(ref _isSquareRootButtonEnabled, value); }
        }


        private string _entry;
        public string Entry
        {
            get { return _entry; }
            private set
            {
                SetProperty(ref _entry, value);
                EntryLabelFontSize = TextSettings.FontSizeByTextLength(LabelType.Entry, value.Length);

                IsSquareRootButtonEnabled = !_entry.StartsWith("-");

                ((Command)PlusMinusCommand)?.ChangeCanExecute();
            }
        }


        private string _output;
        public string Output
        {
            get { return _output; }
            private set
            {
                SetProperty(ref _output, value);
                OutputLabelFontSize = TextSettings.FontSizeByTextLength(LabelType.Output, value.Length);
            }
        }


        private int _entryLabelFontSize;
        public int EntryLabelFontSize
        {
            get { return _entryLabelFontSize; }
            set { SetProperty(ref _entryLabelFontSize, value); }
        }

        private int _outputLabelFontSize;
        public int OutputLabelFontSize
        {
            get { return _outputLabelFontSize; }
            set { SetProperty(ref _outputLabelFontSize, value); }
        }

        #endregion

        #region Commands

        public ICommand DigitCommand { get; private set; }
        private void digitCommand(string arg)
        {
            if (_calculator.HasOperation && !_calculator.HasSecondNumber)
            {
                Entry = arg;
            }
            else if ((_calculator.HasOperation && _calculator.HasSecondNumber) ||
                (!_calculator.HasOperation && !_calculator.HasPreviousOperation))
            {
                string futureEntry = Entry + arg;
                if (futureEntry.StartsWith("0") && !futureEntry.StartsWith("0."))
                {
                    futureEntry = futureEntry.Substring(1);
                }
                Entry = futureEntry;
            }
            else
            {
                _calculator.Cancel();
                Entry = arg;
            }

            if (Entry == ".")
            {
                Entry = "0.";
            }

            _calculator.NumberEntered(Entry);
            RefreshCanExecutes();
        }


        public ICommand DotCommand { get; private set; }
        public ICommand CancelCommand { get; private set; }
        public ICommand CleanEntryCommand { get; private set; }
        public ICommand SimpleOperationCommand { get; private set; }
        public ICommand EqualsCommand { get; private set; }
        public ICommand BackspaceCommand { get; private set; }
        public ICommand PlusMinusCommand { get; private set; }
        public ICommand SquareCommand { get; private set; }
        public ICommand BackOperationCommand { get; private set; }
        public ICommand SquareRootCommand { get; private set; }
        public ICommand PercentCommand { get; private set; }
        public ICommand ModuleCommand { get; private set; }

        public ICommand MC_Command { get; private set; }
        public ICommand MR_Command { get; private set; }
        public ICommand MPlus_Command { get; private set; }
        public ICommand MMinus_Command { get; private set; }
        public ICommand MS_Command { get; private set; }

        #endregion

        private void RefreshCanExecutes()
        {
            ((Command)BackspaceCommand).ChangeCanExecute();
            ((Command)DotCommand).ChangeCanExecute();
            ((Command)PlusMinusCommand).ChangeCanExecute();

            IsDigitButtonEnabled = (_entry.Replace(" ", "").Replace("-", "").Replace(".", "").Length
                    < TextSettings.MaxDigitsInEntryNumber);
        }

        private void RefreshMemoryCanExecutes()
        {
            ((Command)MC_Command).ChangeCanExecute();
            ((Command)MR_Command).ChangeCanExecute();
            ((Command)MPlus_Command).ChangeCanExecute();
            ((Command)MMinus_Command).ChangeCanExecute();
            ((Command)MS_Command).ChangeCanExecute();
        }
    }
}


