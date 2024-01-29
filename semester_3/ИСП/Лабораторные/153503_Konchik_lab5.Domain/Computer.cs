namespace _153503_Konchik_lab5.Domain
{
    
    public class Computer
    {
        public Winchester Winchester { get; set; } = new();

        public Computer(Winchester winchester)
        {
            Winchester = winchester;
        }

        public Computer()
        {

        }

        public void Print()
        {
            Winchester.Print();
        }
    }
}