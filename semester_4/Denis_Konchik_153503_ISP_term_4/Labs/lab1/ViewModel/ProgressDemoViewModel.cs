using lab1.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace lab1.ViewModel
{
    public class ProgressDemoViewModel : BaseViewModel
    {
        private Integral _integral;

        private CancellationTokenSource _cancelTokenSource;

        public ProgressDemoViewModel(Integral intergral)
        {
            _integral = intergral;
            _integral.ProgressChanged += _progressHandler;

            #region Properties Initializing 

            StatusText = "Welcome to .NET MAUI!";
            ProgressText = "0%";
            ProgressPercent = 0;
            StartButtonIsEnabled = true;
            CancelButtonIsEnabled = false;

            #endregion

            #region Commands Initializing 

            StartButtonCommand = new Command(() =>
            {
                _cancelTokenSource = new();
                _integral.CalculateAsync(_cancelTokenSource.Token);

                StartButtonIsEnabled = false;
                CancelButtonIsEnabled = true;
                StatusText = "Вычисление";
            }, () => StartButtonIsEnabled);

            CancelButtonCommand = new Command(() =>
            {
                _cancelTokenSource.Cancel();
                _cancelTokenSource.Dispose();

                StartButtonIsEnabled = true;
                CancelButtonIsEnabled = false;
                StatusText = "Задание отменено";
            }, () => CancelButtonIsEnabled);

            #endregion

        }

        #region Properties

        private string _progressText = string.Empty;
        public string ProgressText
        {
            get { return _progressText; }
            set { SetProperty(ref _progressText, value); }
        }

        private bool _startButtonIsEnabled;
        public bool StartButtonIsEnabled
        {
            get { return _startButtonIsEnabled; }
            set { SetProperty(ref _startButtonIsEnabled, value); }
        }

        private bool _cancelButtonIsEnabled;
        public bool CancelButtonIsEnabled
        {
            get { return _cancelButtonIsEnabled; }
            set { SetProperty(ref _cancelButtonIsEnabled, value); }
        }

        private string _statusText;
        public string StatusText
        {
            get { return _statusText; }
            set { SetProperty(ref _statusText, value); }
        }

        private double _progressPercent;
        public double ProgressPercent
        {
            get { return _progressPercent; }
            set { SetProperty(ref _progressPercent, value); }
        }
        #endregion

        #region Commands

        public ICommand StartButtonCommand { get; set; }
        public ICommand CancelButtonCommand { get; set; }

        #endregion


        private void _progressHandler(double value, bool calculated)
        {
            if (calculated)
            {
                StatusText = string.Format("{0:f8}", value).Replace(",", ".");
                ProgressText = "100.00%";
                StartButtonIsEnabled = true;
                CancelButtonIsEnabled = false;
            }
            else
            {
                ProgressText = string.Format("{0:f2}%", value).Replace(",", ".");
                ProgressPercent = value / 100;
            }
        }
    }
}
