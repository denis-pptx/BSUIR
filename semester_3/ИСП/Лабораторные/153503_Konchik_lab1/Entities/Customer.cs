using _153503_Konchik_lab1.Collections;

namespace _153503_Konchik_lab1.Entities
{
    

    // Абонент
    class Customer
    {
        // Тип абонента
        public CustomerType customerType { get; private set; }

        // "тариф - число вызовов"
        public MyCustomCollection<(Rate rate, int callsNumber)> CallsList { get; private set; } 

        // Номер текущего тарифа в CallsList
        private int current;

        // Имя абонента
        public string Name { get; private set; }

        // Стоимость всех вызовов
        public double GetCallsSum(bool withType)
        {
            double sum = 0;

            foreach (var call in CallsList)
                sum += call.rate.Payment * call.callsNumber;

            if (withType && customerType == CustomerType.VIP)
                sum *= (1 - RateDiscount());

            return sum;
        }

        // Число всех вызовов
        public int GetCallsNum()
        {
            int num = 0;
            foreach (var call in CallsList)
                num += call.callsNumber;

            return num;
        }

        // Выбрать тариф
        public void SelectRate(Rate rate)
        {

            for (int i = 0; i < CallsList.Count; i++)
            {
                // Если такой тариф уже есть
                if (CallsList[i].rate == rate)
                {
                    current = i;
                    return;
                }
            }

            // Если такого тарифа нету
            CallsList.Add((rate, 0));
            current = CallsList.Count - 1;
        }

        // Совершить вызов
        public void MakeCall()
        {
            if (CallsList.Count == 0)
                throw new Exception("Не выбран тариф");

            (Rate rate, int callsNumber) = CallsList[current];
            CallsList[current] = (rate, ++callsNumber);
        }

        // Информация по текущему тарифу
        public (Rate rate, int number) GetCurrentRateInfo()
        {
            return CallsList[current];
        }

        // Скидка тарифа
        public double RateDiscount()
        {
            if (customerType == CustomerType.VIP)
                return 0.2;

            return 0;
        }

        // Конструктор
        public Customer(string name, CustomerType customerType)
        {
            Name = name;
            this.customerType = customerType;

            CallsList = new MyCustomCollection<(Rate rate, int number)>();
        }

    }
}

