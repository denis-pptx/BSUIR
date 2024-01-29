using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4;

internal class FileService : IFileService<Student>
{
    public IEnumerable<Student> ReadFile(string fileName)
    {
        
        using BinaryReader reader = new BinaryReader(new FileStream(fileName, FileMode.Open));

        
        while (reader.PeekChar() != -1)
        {
            string name = "";
            int age = new();
            int group = new();
            bool isBudget = new();

            try
            {
                name = reader.ReadString();
                age = reader.ReadInt32();
                group = reader.ReadInt32();
                isBudget = reader.ReadBoolean();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            yield return new Student(name, age, group, isBudget);
        }

    }

    public void SaveData(IEnumerable<Student> data, string fileName)
    {
        if (File.Exists(fileName))
            File.Delete(fileName);

        try
        {
            using BinaryWriter writer = new BinaryWriter(new FileStream(fileName, FileMode.Create));

            foreach (Student student in data)
            {
                writer.Write(student.Name);
                writer.Write(student.Age);
                writer.Write(student.Group);
                writer.Write(student.IsBudget);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}

