using _153503_Konchik_lab2.Collections;
using _153503_Konchik_lab2.Entities;

namespace _153503_Konchik_lab2;
class Program
{
    static int Main()
    {
        ATE ate = new ATE();

        Journal journal = new Journal();
        ate.RateAdded += journal.OnRateAdded;
        ate.CustomerAdded += journal.OnCustomerAdded;
        ate.CustomerRemoved += journal.OnCustomerRemoved;

        ate.CustomerCalled += (customerName) =>
        {
            Console.WriteLine($"{customerName} совершил(а) звонок");
        };

        ate.AddRate(name: "Безлимитище", payment: 1);
        ate.AddRate(name: "Безлимитище+", payment: 5);
        ate.AddRate(name: "Комфорт S", payment: 3);
        ate.AddRate(name: "Комфорт XXL", payment: 7);

        ate.AddCostumer("Денис", CustomerType.VIP);
        ate.AddCostumer("Иван", CustomerType.usual);
        ate.AddCostumer("Степан", CustomerType.usual);


        ate.LogIn("Иван");
        ate.SelectRate("Безлимитище+");
        for (int i = 0; i < 10; i++) { ate.MakeCall(); }
        ate.SelectRate("Комфорт XXL"); ate.MakeCall();
        ate.LogOut();

        ate.LogIn("Денис");
        ate.SelectRate("Безлимитище"); ate.MakeCall();
        ate.SelectRate("Безлимитище+"); ate.MakeCall();
        ate.SelectRate("Комфорт S"); ate.MakeCall();
        ate.SelectRate("Безлимитище"); ate.MakeCall();
        ate.LogOut();

        ate.RemoveCostumer("Степан");

        ate.PrintInfoByName("Денис");
        ate.PrintInfoByName("Иван");


        ate.PrintTotalSum();


        journal.PrintAddedCustomers();
        journal.PrintRemovedCustomers();
        journal.PrintAddedRates();
        


        return 0;


    }
}