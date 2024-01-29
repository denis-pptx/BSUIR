namespace _153503_Konchik_lab3.Entities;

class Rate
{
    private double payment;
    public double Payment
    {
        get { return payment; }

        private set { payment = value < 0 ? 0 : value; }
    }

    public string Name { get; private set; }

    public Rate(string name, double payment)
    {
        Name = name;
        Payment = payment;
    }
}

