namespace _153503_Konchik_lab1.Entities
{
    // Тариф
    class Rate
    {
        // Плата за звонок
        private double payment;
        public double Payment
        {
            get { return payment; }

            private set { payment = value < 0 ? 0 : value; }
        }

        // Имя тарифа
        public string Name { get; private set; }

        // Конструктор
        public Rate(string name, double payment)
        {
            Name = name;
            Payment = payment;
        }
    }
}
