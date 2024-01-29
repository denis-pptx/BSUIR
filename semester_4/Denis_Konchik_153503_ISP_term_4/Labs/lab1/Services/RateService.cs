using lab1.Entities;
using System.Net.Http.Json;

namespace lab1.Services;

public class RateService : IRateService
{

    private HttpClient _httpClient;

    private List<Currency> _currencies;

    public async Task<IEnumerable<Rate>> GetRates(DateTime date)
    {

        object data = await _httpClient.GetFromJsonAsync(_httpClient.BaseAddress.ToString() +
            $"?ondate={date.Year}-{date.Month}-{date.Day}&periodicity=0", typeof(IEnumerable<Rate>));

        if (data is IEnumerable<Rate> rates)
        {
            return rates;
        }
        else
        {
            throw new HttpRequestException();
        }
    }

    public IEnumerable<Currency> GetCurrencies()
    {
        return _currencies;
    }

    public async Task<IEnumerable<Rate>> GetRatesByCurrencies(IEnumerable<Currency> currencies, DateTime date)
    {
        var allRates = await GetRates(date);
        IEnumerable<Rate> rates = new List<Rate>();

        return from rate in allRates
               from currency in currencies
               where rate.Cur_Abbreviation == currency.Cur_Abbreviation
               where rate.Cur_Abbreviation != "BYN"
               select rate;
    }


    public decimal ConvertCurrency(Currency fromCurrency, Currency toCurrency,
        decimal fromValue, IEnumerable<Rate> rates)
    {
        if (fromCurrency.Cur_Abbreviation == toCurrency.Cur_Abbreviation)
        {
            return fromValue;
        }

        decimal fromValueInBYN = 0;
        if (fromCurrency.Cur_Abbreviation == "BYN")
        {
            fromValueInBYN = fromValue;
        }
        else
        {
            var fromRate = rates.FirstOrDefault(r => r.Cur_Abbreviation == fromCurrency.Cur_Abbreviation);
            if (fromRate is null)
            {
                return 0;
            }
            fromValueInBYN = (fromRate.Cur_OfficialRate / fromRate.Cur_Scale) * fromValue;
        }

        decimal toValue = 0;
        if (toCurrency.Cur_Abbreviation == "BYN")
        {
            toValue = fromValueInBYN;
        }
        else
        {
            var toRate = rates.FirstOrDefault(r => r.Cur_Abbreviation == toCurrency.Cur_Abbreviation);
            if (toRate is null)
            {
                return 0;
            }
            toValue = (fromValueInBYN / toRate.Cur_OfficialRate) * toRate.Cur_Scale;
        }

        return toValue;
    }

   
    public RateService(HttpClient httpClient)
    {
        _httpClient = httpClient;

        _currencies = new List<Currency>()
        {
            new Currency()
            {
                Cur_Abbreviation = "BYN",
                Cur_Name = "Белорусский рубль"
            },
            new Currency()
            {
                Cur_Abbreviation = "RUB",
                Cur_Name = "Российский рубль"
            },
            new Currency()
            {
                Cur_Abbreviation = "EUR",
                Cur_Name = "Евро"
            },
            new Currency()
            {
                Cur_Abbreviation = "USD",
                Cur_Name = "Доллар США"
            },
            new Currency()
            {
                Cur_Abbreviation = "CHF",
                Cur_Name = "Швейцарский франк"
            },
            new Currency()
            {
                Cur_Abbreviation = "CNY",
                Cur_Name = "Китайский юань"
            },
            new Currency()
            {
                Cur_Abbreviation = "GBP",
                Cur_Name = "Фунт стерлингов"
            }
        };
    }
}
