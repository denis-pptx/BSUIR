using _153503_Konchik_lab5.Domain;
using _153503_Konchik_lab5.Serializer;

class Program
{
    public static void Main()
    {
        List<Computer> computers = new();

        computers.Add(new Computer(new Winchester() { 
            Manufacturer = "Toshiba",              
            Interface = "SATA",
            FormFactor = 3.5,
            RotationSpeed = 5400,
            DataTransferRate = 50,
            BufferSize = 8
        }));
        computers.Add(new Computer(new Winchester()
        {
            Manufacturer = "Seagate",
            Interface = "ATA",
            FormFactor = 2.5,
            RotationSpeed = 7200,
            DataTransferRate = 74,
            BufferSize = 32
        }));
        computers.Add(new Computer(new Winchester()
        {
            Manufacturer = "WD",
            Interface = "SATA",
            FormFactor = 3.5,
            RotationSpeed = 4200,
            DataTransferRate = 60,
            BufferSize = 64
        }));
        computers.Add(new Computer(new Winchester()
        {
            Manufacturer = "Apple",
            Interface = "ATA",
            FormFactor = 2.5,
            RotationSpeed = 10000,
            DataTransferRate = 110,
            BufferSize = 64
        }));
        computers.Add(new Computer(new Winchester()
        {
            Manufacturer = "Hitachi",
            Interface = "SATA",
            FormFactor = 3.5,
            RotationSpeed = 5400,
            DataTransferRate = 90,
            BufferSize = 16
        }));
        computers.Add(new Computer(new Winchester()
        {
            Manufacturer = "Samsung",
            Interface = "SATA",
            FormFactor = 3.5,
            RotationSpeed = 7200,
            DataTransferRate = 70,
            BufferSize = 32
        }));


        ColorWriteLine("ИСХОДНЫЕ ВИНЧЕСТЕРЫ В КОМПЬЮТЕРАХ");
        foreach (var computer in computers)
        {
            computer.Print();
        }

        string filePath = @"D:\Studies\course_2\sem_3\ИСП\Лабораторные\153503_Konchik_lab5\serialization\";
        Serializer serializer = new();

        serializer.SerializeByLINQ(computers, filePath + "computers_LINQ_XML.xml");
        ColorWriteLine("LINQ_XML ДЕСЕРИАЛИЗАЦИЯ");
        foreach (var computer in serializer.DeSerializeByLINQ(filePath + "computers_LINQ_XML.xml"))
        {
            computer.Print();
        }

        serializer.SerializeXML(computers, filePath + "computers_XML.xml");
        ColorWriteLine("XML ДЕСЕРИАЛИЗАЦИЯ");
        foreach (var computer in serializer.DeSerializeXML(filePath + "computers_XML.xml"))
        {
            computer.Print();
        }

        serializer.SerializeJSON(computers, filePath + "computers_JSON.json");
        ColorWriteLine("JSON ДЕСЕРИАЛИЗАЦИЯ");
        foreach (var computer in serializer.DeSerializeJSON(filePath + "computers_JSON.json"))
        {
            computer.Print();
        }

    }

    private static void ColorWriteLine(string str, ConsoleColor consoleColor = ConsoleColor.Green)
    {
        Console.ForegroundColor = consoleColor;
        Console.WriteLine("\n" + str);
        Console.ResetColor();
    }
}