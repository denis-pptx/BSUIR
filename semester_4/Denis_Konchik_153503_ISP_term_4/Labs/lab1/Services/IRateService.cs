using lab1.Entities;

namespace lab1.Services;

public interface IRateService
{
    Task<IEnumerable<Rate>> GetRates(DateTime date);

    IEnumerable<Currency> GetCurrencies();

    Task<IEnumerable<Rate>> GetRatesByCurrencies(IEnumerable<Currency> currencies, DateTime date);

    decimal ConvertCurrency(Currency fromCurrency, Currency toCurrency, decimal fromValue, IEnumerable<Rate> rates);
}
