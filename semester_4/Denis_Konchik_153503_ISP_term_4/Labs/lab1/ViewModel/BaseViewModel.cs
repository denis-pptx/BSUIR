using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace lab1.ViewModel
{
    public class BaseViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected bool SetProperty<T>(ref T property, T value, [CallerMemberName] string propertyName = "")
        {
            if (System.Object.Equals(property, value))
            {
                return false;
            }

            property = value;

            OnPropertyChanged(propertyName);
            return true;
        }

        protected void OnPropertyChanged([CallerMemberName] string propertyName = "")
        {
            this.PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private bool _isBusy;
        public bool IsBusy
        {
            get { return _isBusy; }
            set 
            { 
                SetProperty(ref _isBusy, value);
                SetProperty(ref _isNotBusy, !value, nameof(IsNotBusy));
            }
        }

        private bool _isNotBusy;
        public bool IsNotBusy
        {
            get { return _isNotBusy; }
            set 
            { 
                SetProperty(ref _isNotBusy, value);
                SetProperty(ref _isBusy, !value, nameof(IsBusy));
            }
        }

        private bool _isRefreshing;

        public bool IsRefreshing
        {
            get { return _isRefreshing; }
            set { SetProperty(ref _isRefreshing, value); }
        }


        public BaseViewModel()
        {
            IsBusy = false;
            IsNotBusy = true;
            IsRefreshing = false;
        }
    }
}
