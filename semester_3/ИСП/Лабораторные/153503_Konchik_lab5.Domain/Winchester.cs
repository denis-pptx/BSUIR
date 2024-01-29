
namespace _153503_Konchik_lab5.Domain
{
    
    public class Winchester
    {
        public string Manufacturer { get; set; } = "";
        public string Interface { get; set; } = "";
        public double FormFactor { get; set; }
        public double RotationSpeed { get; set; }
        public double DataTransferRate { get; set; }
        public double BufferSize { get; set; }

        public void Print()
        {
            Console.WriteLine($"\nПроизводитель: {Manufacturer}" +
                $"\nИнтерфейс: {Interface}" +
                $"\nФорм-фактор: {FormFactor} (дюйм)" +
                $"\nСкорость вращения: {RotationSpeed} (об/мин)" +
                $"\nСкорость передачи данных: {DataTransferRate} (Мб/с)" +
                $"\nОбъем буфера: {BufferSize} (Мб)");
        }

        public Winchester()
        {

        }
    }
}
