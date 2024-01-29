namespace lab4;
class Program
{
    private static void ColorWriteLine(string str, ConsoleColor consoleColor = ConsoleColor.Green)
    {
        Console.ForegroundColor = consoleColor;
        Console.WriteLine(str);
        Console.ResetColor(); 
    }

    public static void Main()
    {
        List<Student> students = new() 
        {
            new Student("Денис", 18, 153503, true),
            new Student("Синед", 81, 305351, false),
            new Student("Иван", 19, 053504, false),
            new Student("Владимир", 17, 253502, true),
            new Student("Алексей", 21, 951004, true)

        };
     

        FileService fileService = new();
        string path = @"D:\Studies\course_2\sem_3\ИСП\Лабораторные\lab4\Файлы\";

        string fileName = "list.txt";
        fileService.SaveData(students, path + fileName);

        string newFileName = "newList.txt";
        if (File.Exists(path + newFileName))
        {
            File.Delete(path + newFileName);
        }
        File.Move(path + fileName, path + newFileName);


        ColorWriteLine("ИСХОДНАЯ КОЛЛЕКЦИЯ");
        foreach (var student in students)
        {
            Console.WriteLine(student.ToString() + "\n");
        }


        List<Student> studentsSorted = fileService.ReadFile(path + newFileName).ToList();
        studentsSorted = studentsSorted.OrderBy(student => student, new MyCustomComparer()).ToList();

        ColorWriteLine("СОРТИРОВКА ПО ИМЕНИ");
        foreach (var student in studentsSorted)
        {
            Console.WriteLine(student.ToString() + "\n");
        }


        studentsSorted = studentsSorted.OrderBy(student => student.Age).ToList();

        ColorWriteLine("СОРТИРОВКА ПО ВОЗРАСТУ");
        foreach (var student in studentsSorted)
        {
            Console.WriteLine(student.ToString() + "\n");
        }
    }
}