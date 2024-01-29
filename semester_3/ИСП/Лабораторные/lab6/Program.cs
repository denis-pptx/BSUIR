
using System.Reflection;

namespace lab6
{
    class Program
    {
        public static void Main()
        {

            List<Employee> employees = new() 
            { 
                new Employee("Denis", true, 18),
                new Employee("Elena", false, 20),
                new Employee("Evgeniy", true, 19),
                new Employee("Boris", true, 30),
                new Employee("Vladimir", true, 35)
            };

            Console.WriteLine("ИСХОДНЫЕ ДАННЫЕ");
            foreach(var employee in employees)
            {
                Console.WriteLine(employee.ToString());
            }

            string fileName = @"D:\Studies\course_2\sem_3\ИСП\Лабораторные\lab6\list.json";

            Assembly asm = Assembly
                .LoadFrom(@"D:\Studies\course_2\sem_3\ИСП\Лабораторные\lab6\Debug\net6.0\MyLib.dll");

            //foreach(var t in asm.GetTypes())
                //Console.WriteLine(t);
            
            Type? type = asm?
                .GetType("MyLib.FileService`1")?
                .MakeGenericType(typeof(Employee)) ?? null;

            if (type != null)
            {
                object? FileService = Activator.CreateInstance(type);

                MethodInfo? SaveData = type.GetMethod("SaveData");

                MethodInfo? ReadFile = type.GetMethod("ReadFile");

                SaveData?.Invoke(FileService, new object[] { employees, fileName });
                object? result = ReadFile?.Invoke(FileService, new object[] { fileName });

                if (result is List<Employee> collection)
                {
                    Console.WriteLine("JSON ДЕСЕРИАЛИЗАЦИЯ");
                    foreach (var emp in collection)
                    {
                        Console.WriteLine(emp.ToString());
                    }
                }
            }

        }
    }
}