

namespace _153503_Konchik_lab3.Entities;

internal class ATE
{
    // Список абонентов
    private List<Customer> lstCust; 

    // Cловарь тарифов
    private Dictionary<string, Rate> dctRates;

    // Текущий абонент
    private Customer? currentCust;
      

    // Список названий всех тарифов, отсортированный по стоимости
    public IEnumerable<string> RateNamesSortedByPayment()
    {
        var sortedRateNames = from rate in dctRates
                              orderby rate.Value.Payment
                              select new string($"{rate.Value.Name} — {rate.Value.Payment}");

        return sortedRateNames;
    }

    // Общая стоимость всех выполненных на АТС звонков
    public double GetTotalSum()
    {
        return (from cust in lstCust 
                select cust.GetCallsSum()).Sum();
    }

    // Общая стоимость звонков абонента
    public double GetTotalCustSum(string custName)
    {
        Customer? customer = GetCustByName(custName);
        if (customer == null)
        {
            throw new Exception("Несуществующий абонент");
        }
        else
        {
            return customer.GetCallsSum();
        }
    }

    // Заплатил больше всех
    public string GetMaxPaymentCustName()
    {
        return (from cust in lstCust
                orderby cust.GetCallsSum() descending
                select cust.Name).First();
    }

    // Сколько абонентов заплатили больше суммы
    public int NumberOfCustPayedMoreThan(double sum)
    {
        return lstCust.Where(cust => cust.GetCallsSum() > sum)
            .Aggregate(0, (number, sum) => ++number);
    }

    // Список сумм абонента, сгруппированных по тарифу
    public void PrintGroupedSumsByCustName(string custName)
    {
        Customer? customer = GetCustByName(custName);
        if (customer == null)
        {
            throw new Exception("Несуществующий абонент");
        }
        else
        {
            Console.WriteLine($"\nАбонент: {custName}");
            var sums = customer.GroupSumByRate();

            foreach (var rate in sums)
            {
                Console.Write($"{rate.Key}: \t");

                foreach (var sum in rate)
                    Console.WriteLine(sum);
            }
        }

            
            
    }

    // Абонент по имени
    private Customer? GetCustByName(string name)
    {

        for (int i = 0; i < lstCust.Count; i++)
        {
            try
            {
                if (lstCust[i].Name == name)
                    return lstCust[i];
            }
            catch (IndexOutOfRangeException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        return null;
    }

    public ATE()
    {
        lstCust = new();
        dctRates = new();
    }

    // Добавить абонента
    public void AddCostumer(string name)
    {
        lstCust.Add(new Customer(name));
        CustomerAdded?.Invoke(name);
    }

    // Удалить абонента
    public void RemoveCostumer(string name)
    {
        Customer? customer = GetCustByName(name);
        if (customer != null)
        {
            lstCust.Remove(customer);
            CustomerRemoved?.Invoke(name);

            if (currentCust == customer)
                currentCust = null;
        }
    }
        
    // Авторизоваться
    public void LogIn(string name)
    {
        if (currentCust != null)
            throw new Exception("Прошлый абонент не вышел");

        currentCust = GetCustByName(name);

        if (currentCust == null)
            throw new Exception("Несуществующий абонент");
    }

    // Выйти
    public void LogOut() =>
        currentCust = null;

    // Добавить тариф
    public void AddRate(string name, double payment)
    {
        dctRates.TryAdd(name, new Rate(name, payment));
        RateAdded?.Invoke(name);
    }

    // Выбрать тариф
    public void SelectRate(string name)
    {
        if (currentCust == null)
            throw (new Exception("Абонент не авторизован"));

        if (dctRates.TryGetValue(name, out Rate? rate))
        {
            currentCust?.SelectRate(rate);
        }
        else { 
            throw (new Exception("Несуществующий тариф"));
        }
    }

    // Совершить вызов
    public void MakeCall()
    {
        if (currentCust == null)
            throw new Exception("Несуществующий абонент");

        currentCust.MakeCall();
        CustomerCalled?.Invoke(currentCust.Name);
    }

    // Распечатать информацию по имени абонента
    public void PrintInfoByName(string name)
    {
        Customer? customer = GetCustByName(name);

        if (customer == null)
            throw new Exception("Несуществующий абонент");
        else
        {
            Console.WriteLine("\n==================================================");
            Console.WriteLine($"Имя: {customer.Name}");
            Console.WriteLine($"Текущий тариф: {customer.GetCurrentRateInfo().rate.Name}");
            Console.WriteLine($"Стоимть за вызов: {customer.GetCurrentRateInfo().rate.Payment}");

            Console.WriteLine($"\nОбщая стоимость вызовов: {Math.Round(customer.GetCallsSum(), 2)}");
               

            Console.WriteLine($"Общее количество вызовов: {customer.GetCallsNum()}");

            Console.WriteLine("\nИстория (тариф — [стоимость за вызов] — вызовы): ");

            foreach (var call in customer.CallsList)
                Console.WriteLine($"  {call.rate.Name}\t — \t[{call.rate.Payment}]\t — \t{call.callsNumber}");

            Console.WriteLine("\n==================================================");
        }
    }

    public event Action<string>? RateAdded;
    public event Action<string>? CustomerAdded;
    public event Action<string>? CustomerRemoved;
    public event Action<string>? CustomerCalled;
}


