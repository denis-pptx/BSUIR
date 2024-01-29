using _153503_Konchik_lab1.Collections;
using System.Collections;

namespace _153503_Konchik_lab1.Enumerators
{
    class MyCustomCollectionEnumerator<T> : IEnumerator<T>
    {
        private Node<T>? head;
        private Node<T>? current;
        private bool reseted;
        public MyCustomCollectionEnumerator(Node<T>? head)
        {
            this.head = head;
            current = null;
            reseted = true;
        }

        public T Current
        {
            get
            {
                if (current == null)
                {
                    throw new InvalidOperationException("current is null");
                }
                else
                {
                    return current.data;
                }
            }
        }

        object IEnumerator.Current => throw new NotImplementedException();
        public bool MoveNext()
        {
            if (reseted == true)
            {
                reseted = false;
                current = head;
            }
            else
            {
                current = current?.next ?? null;     
            }

            if (current != null)
                return true;
            else
                return false;
        }

        public void Reset()
        {
            current = null;
            reseted = true;
        }
        public void Dispose() { }
    }
}
