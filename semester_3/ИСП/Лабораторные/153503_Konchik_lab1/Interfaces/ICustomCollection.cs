

namespace _153503_Konchik_lab1.Interfaces
{
    internal interface ICustomCollection<T>
    {
        T this[int index] { get; set; }
        void Reset();
        void Next();
        void Prev();
        T? Current();
        int Count { get; }
        void Add(T item);
        void Remove(T item);
        T RemoveCurrent();
    }
}
