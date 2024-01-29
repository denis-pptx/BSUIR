using _153503_Konchik_lab1.Collections;
using _153503_Konchik_lab1.Entities;

namespace _153503_Konchik_lab1;
class Program
{
    static int Main()
    {
        ATE ate = new ATE();

        ate.AddRate(name: "Безлимитище", payment: 1);
        ate.AddRate(name: "Безлимитище+", payment: 5);
        ate.AddRate(name: "Комфорт S", payment: 3);
        ate.AddRate(name: "Комфорт XXL", payment: 7);

        ate.AddCostumer(name: "Денис", CustomerType.VIP);
        ate.AddCostumer(name: "Иван", CustomerType.usual);



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



        ate.ShowInfoByName("Денис");
        Console.Write("\n\n\n");
        ate.ShowInfoByName("Иван");

        Console.WriteLine($"\n\n\nСтоимость всех вызовов на АТС: \n" +
            $"  с учетом статуса абонентов: {ate.GetTotalSum(withType: true)}\n" +
            $"  без учета статуса абонентов: {ate.GetTotalSum(withType: false)}");


        return 0;


    }
}