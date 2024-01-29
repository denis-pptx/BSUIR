
namespace _153503_Konchik_lab1.Collections
{
    class Node<V>
    {
        public Node<V>? next;
        public Node<V>? prev;
        public V data;
        public Node(V data)
        {
            this.data = data;
        }
    }
}
