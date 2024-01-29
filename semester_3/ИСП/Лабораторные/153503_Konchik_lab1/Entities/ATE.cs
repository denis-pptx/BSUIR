using _153503_Konchik_lab1.Collections;

namespace _153503_Konchik_lab1.Entities
{
    // Автоматическая телефонная станция
    internal class ATE
    {
        // Абоненты
        private MyCustomCollection<Customer> lstCust;

        // Тарифы
        private MyCustomCollection<Rate> lstRates;

        // Текущий абонент
        private Customer? currentCust;
      
        // Абонент по имени
        private Customer? GetCustByName(string name)
        {
            foreach (var Customer in lstCust)
            {
                if (Customer.Name == name)
                {
                    return Customer;
                }
            }
            return null;
        }

        // Тариф по названию
        private Rate? GetRateByName(string name)
        {
            foreach (var Rate in lstRates)
            {
                if (Rate.Name == name)
                {
                    return Rate;
                }
            }
            return null;
        }

        // Конструктор
        public ATE()
        {
            lstCust = new MyCustomCollection<Customer>();
            lstRates = new MyCustomCollection<Rate>();
        }

        // Добавить абонента
        public void AddCostumer(string name, CustomerType customerType) =>
            lstCust.Add(new Customer(name, customerType));
        
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
        public void AddRate(string name, double payment) =>
            lstRates.Add(new Rate(name, payment));

        // Выбрать тариф
        public void SelectRate(string name)
        {
            if (currentCust == null)
                throw (new Exception("Абонент не авторизован"));

            currentCust.SelectRate(GetRateByName(name) ?? 
                throw(new Exception("Несуществующий тариф")));
        }

        // Совершить вызов
        public void MakeCall()
        {
            if (currentCust == null)
                throw new Exception("Несуществующий абонент");

            currentCust.MakeCall();
        }

        // Информация об абоненте по имени
        public void ShowInfoByName(string name)
        {
            Customer? customer = GetCustByName(name);

            if (customer == null)
                throw new Exception("Несуществующий абонент");
            else
            {
                Console.WriteLine($"Имя: {customer.Name}");
                Console.WriteLine($"Статус: {customer.customerType.ToString()}");
                Console.WriteLine($"Текущий тариф: {customer.GetCurrentRateInfo().rate.Name}");
                Console.WriteLine($"Стоимть за вызов: {customer.GetCurrentRateInfo().rate.Payment}");

                Console.WriteLine($"\nОбщая стоимость вызовов (без учета статуса): {Math.Round(customer.GetCallsSum(withType: false), 2)}");
                Console.WriteLine($"Общая стоимость вызовов (с учетом статуса): {Math.Round(customer.GetCallsSum(withType: true), 2)}");
                Console.WriteLine($"Итого скидка: {Math.Round(customer.GetCallsSum(withType: false) - customer.GetCallsSum(withType: true))} " +
                                  $"({Math.Round(customer.RateDiscount() * 100)}%)");
                Console.WriteLine($"Общее количество вызовов: {customer.GetCallsNum()}");

                Console.WriteLine("\nИстория (тариф — [стоимость за вызов] — вызовы): ");

                foreach (var call in customer.CallsList)
                    Console.WriteLine($"  {call.rate.Name}\t — \t[{call.rate.Payment}]\t — \t{call.callsNumber}");
            }
        }

        // Стоимость всех выполненных звонков
        public double GetTotalSum(bool withType)
        {
            double totalSum = 0;

            foreach (var Customer in lstCust)
            {
                totalSum += Customer.GetCallsSum(withType);
            }

            return totalSum;
        }
    }
}

