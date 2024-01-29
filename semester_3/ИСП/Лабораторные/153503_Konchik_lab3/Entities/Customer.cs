
namespace _153503_Konchik_lab3.Entities;

class Customer
{

    // "тариф - число вызовов"
    public List<(Rate rate, int callsNumber)> CallsList { get; private set; } 


    // Номер текущего тарифа в CallsList
    private int current;

    // Имя абонента
    public string Name { get; private set; }

    // Стоимость вызовов
    public double GetCallsSum()
    {
        return (from item in CallsList 
                select item.callsNumber * item.rate.Payment).Sum();
    }

    public IEnumerable<IGrouping<string, double>> GroupSumByRate()
    {
        return (from item in CallsList
             group (item.rate.Payment * item.callsNumber) by item.rate.Name);
    }

    // Число вызовов
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

    // Информация о текущем тарифе
    public (Rate rate, int number) GetCurrentRateInfo()
    {
        return CallsList[current];
    }



    public Customer(string name)
    {
        Name = name;
        CallsList = new();
    }

}


