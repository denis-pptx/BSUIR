using _153503_Konchik_lab2.Collections;


namespace _153503_Konchik_lab2.Entities
{
    internal class Journal
    {
        private MyCustomCollection<string> addedRates;
        private MyCustomCollection<string> addedCustomers;
        private MyCustomCollection<string> removedCustomers;
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
            addedRates = new MyCustomCollection<string>();
            addedCustomers = new MyCustomCollection<string>();
            removedCustomers = new MyCustomCollection<string>();
        }
    }
}
