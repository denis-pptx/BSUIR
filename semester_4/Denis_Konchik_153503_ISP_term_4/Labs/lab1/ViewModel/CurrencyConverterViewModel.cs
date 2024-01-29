using System.Windows.Input;
using lab1.Entities;
using lab1.Services;
using lab1.Helpers;
using System.Collections.ObjectModel;
using MvvmHelpers;
namespace lab1.ViewModel;

public class CurrencyConverterViewModel : BaseViewModel
{
    private IRateService _rateService;

    private bool _isUserInput = true;
    public CurrencyConverterViewModel(IRateService rateService)
    {
        _rateService = rateService;
        
        Currencies = _rateService.GetCurrencies();

        SelectedDate = DateTime.Today;
        MaxDate = DateTime.Today;
        MinDate = new DateTime(year: 1996, month: 1, day: 1);

        _firstCurrencyValue = "0";
        _secondCurrencyValue = "0";

        SelectedFirstCurrency = Currencies.FirstOrDefault(c => c.Cur_Abbreviation == "USD");
        SelectedSecondCurrency = Currencies.FirstOrDefault(c => c.Cur_Abbreviation == "BYN");

        RefreshDateCommand = new Command(() => SelectedDate = DateTime.Today);
    }


    private async void _updateFirstCurrencyValue()
    {
        if (Connectivity.Current.NetworkAccess == NetworkAccess.None)
        {
            await App.Current.MainPage.DisplayAlert("Alert", "No internet access", "OK");
            return;
        }

        var rates = await _rateService.GetRates(_selectedDate);

        decimal value = _rateService.ConvertCurrency(_selectedSecondCurrency, _selectedFirstCurrency,
            CurrencyConverterHelper.StringToDecimal(_secondCurrencyValue), rates);

        _firstCurrencyValue = CurrencyConverterHelper.DecimalToString(value);

        _isUserInput = false;
        OnPropertyChanged(nameof(FirstCurrencyValue));
        _isUserInput = true;
    }

    private async void _updateSecondCurrencyValue()
    {
        if (Connectivity.Current.NetworkAccess == NetworkAccess.None)
        {
            await App.Current.MainPage.DisplayAlert("Alert", "No internet access", "OK");
            return;
        }

        var rates = await _rateService.GetRates(_selectedDate);

        decimal value = _rateService.ConvertCurrency(_selectedFirstCurrency, _selectedSecondCurrency,
            CurrencyConverterHelper.StringToDecimal(_firstCurrencyValue), rates);
        
        _secondCurrencyValue = CurrencyConverterHelper.DecimalToString(value);

        _isUserInput = false;
        OnPropertyChanged(nameof(SecondCurrencyValue));
        _isUserInput = true;
    }

    private async void _updateRates()
    {
        var rates = await _rateService.GetRatesByCurrencies(_rateService.GetCurrencies(), _selectedDate);
        Rates = rates.ToList();
        OnPropertyChanged(nameof(Rates));
    }


    private DateTime _minDate;
    public DateTime MinDate
    {
        get { return _minDate; }
        set { SetProperty(ref _minDate, value); }
    }


    private DateTime _maxDate;
    public DateTime MaxDate
    {
        get { return _maxDate; }
        set { SetProperty(ref _maxDate, value); }
    }


    private DateTime _selectedDate;
    public DateTime SelectedDate
    {
        get { return _selectedDate; }
        set 
        { 
            if (SetProperty(ref _selectedDate, value))
            {
                _updateSecondCurrencyValue();
                _updateRates();
            } 
        }
    }


    private string _firstCurrencyValue;
    public string FirstCurrencyValue
    {
        get { return _firstCurrencyValue; }
        set
        {
            SetProperty(ref _firstCurrencyValue, value);
            
            if (_isUserInput)
            {
                _updateSecondCurrencyValue();
            }
        }
    }

    private string _secondCurrencyValue;
    public string SecondCurrencyValue
    {
        get { return _secondCurrencyValue; }
        set
        {
            SetProperty(ref _secondCurrencyValue, value);

            if (_isUserInput)
            {
                _updateFirstCurrencyValue();
            }
        }
    }


    private Currency _selectedFirstCurrency;
    public Currency SelectedFirstCurrency
    {
        get { return _selectedFirstCurrency; }
        set 
        { 
            if (SetProperty(ref _selectedFirstCurrency, value))
            {
                _updateFirstCurrencyValue();
            }
        }
    }


    private Currency _selectedSecondCurrency;
    public Currency SelectedSecondCurrency
    {
        get { return _selectedSecondCurrency; }
        set 
        { 
            if (SetProperty(ref _selectedSecondCurrency, value))
            {
                _updateSecondCurrencyValue();
            }
        }
    }


    public IEnumerable<Currency> Currencies { get; private set; }

    public List<Rate> Rates { get; set; } = new();

    public ICommand RefreshDateCommand { get; set; }



}
