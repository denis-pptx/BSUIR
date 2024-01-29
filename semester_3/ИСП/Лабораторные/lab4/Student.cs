using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4;

internal class Student
{
    public string? Name { get; set; }
    public int Age { get; set; }
    public int Group { get; set; }
    public bool IsBudget { get; set; }

    private string boolToString(bool flag)
    {
        return flag ? "да" : "нет";
    }

    public Student(string? name, int age, int group, bool isBudget)
    {
        Name = name;
        Age = age;
        Group = group;
        IsBudget = isBudget;
    }

    public Student()
    {

    }

    public override string ToString()
    {
        return new string($"Имя: {Name}\nВозраст: {Age}\n" +
                          $"Группа: {Group}\nБюджет: {boolToString(IsBudget)}");
    }
}

