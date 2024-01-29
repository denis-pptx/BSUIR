namespace _153503_Konchik_lab3.Entities;

internal class Journal
{
    private List<string> addedRates;
    private List<string> addedCustomers;
    private List<string> removedCustomers;
    public void OnRateAdded(string rate) => 
        addedRates.Add(rate);
        

    public void OnCustomerAdded(string customer) =>
        addedCustomers.Add(customer);

    public void OnCustomerRemoved(string customer) =>
        removedCustomers.Add(customer);
        
    public void PrintAddedRates()
    {

        Console.WriteLine("\nДобавленные тарифы:");
        foreach (var name in addedRates)
            Console.WriteLine(name);
    }

    public void PrintAddedCustomers()
    {
        Console.WriteLine("\nДобавленные абоненты:");
        foreach (var name in addedCustomers)
            Console.WriteLine(name);
    }

    public void PrintRemovedCustomers()
    {
        Console.WriteLine("\nУдаленные абоненты:");
        foreach (var name in removedCustomers)
            Console.WriteLine(name);
    }

    public Journal()
    {
        addedRates = new();
        addedCustomers = new();
        removedCustomers = new();
    }
}

