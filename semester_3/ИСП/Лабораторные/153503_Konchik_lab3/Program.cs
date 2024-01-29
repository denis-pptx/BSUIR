using _153503_Konchik_lab3.Entities;

namespace _153503_Konchik_lab3;
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

        ate.AddRate(name: "Комфорт XXL", payment: 7);
        ate.AddRate(name: "Безлимитище", payment: 1);
        ate.AddRate(name: "Безлимитище+", payment: 4);
        ate.AddRate(name: "Комфорт S", payment: 3);
        

        ate.AddCostumer("Денис");
        ate.AddCostumer("Иван");
        ate.AddCostumer("Степан");
        ate.RemoveCostumer("Степан");

        ate.LogIn("Иван");
        ate.SelectRate("Безлимитище+");
        for (int i = 0; i < 10; i++) 
        { 
            ate.MakeCall(); 
        }
        ate.SelectRate("Комфорт XXL"); 
        ate.MakeCall();
        ate.LogOut();

        ate.LogIn("Денис");
        ate.SelectRate("Безлимитище"); 
        ate.MakeCall();
        ate.SelectRate("Безлимитище+"); 
        ate.MakeCall();
        ate.MakeCall();
        ate.SelectRate("Комфорт S"); 
        ate.MakeCall();
        ate.LogOut();


        ate.PrintInfoByName("Денис");
        ate.PrintInfoByName("Иван");


      //  ate.PrintTotalSum();


        journal.PrintAddedCustomers();
        journal.PrintRemovedCustomers();
        journal.PrintAddedRates();

        Console.WriteLine("\n\n\n\n");


        Console.WriteLine("Названия тарифов, отсортированные по стоимости:");
        foreach(var name in ate.RateNamesSortedByPayment())
            Console.WriteLine(name);

        Console.WriteLine("\nОбщая стоимость всех звонков на АТС: {0}", ate.GetTotalSum());
 
        Console.WriteLine("\nЗаплатил больше всех: {0}", ate.GetMaxPaymentCustName());

        int payment = 45;
        Console.WriteLine("\nЗаплатили больше, чем {0}: {1}", payment, ate.NumberOfCustPayedMoreThan(payment));

        ate.PrintGroupedSumsByCustName("Денис");
        ate.PrintGroupedSumsByCustName("Иван");
        return 0;


    }
}