using _153503_Konchik_lab2.Interfaces;
using System.Collections;
using _153503_Konchik_lab2.Exceptions;

namespace _153503_Konchik_lab2.Collections
{
    

    internal class MyCustomCollection<T> : ICustomCollection<T>, IEnumerable<T>
    {
        private Node<T>? head;

        private Node<T>? tail;

        private Node<T>? current;

        private int count;

        public T this[int index] { 
            get
            {
                if (index < 0 || index >= count)
                    throw new IndexOutOfRangeException("index in indexer is out of range");

                Node<T>? pointer = head;
                for (int i = 0; i < index; i++)
                {
                    pointer = pointer.next;
                }
                return pointer.data;
            }
            set
            {
                if (index < 0 || index >= count)
                    throw new ArgumentOutOfRangeException("index in indexer is out of range");

                Node<T>? pointer = head;
                for (int i = 0; i < index; i++)
                {
                    pointer = pointer.next;
                }
                pointer.data = value;
            }
        }

        public int Count => count;

        public void Add(T item)
        {
            Node<T> node = new Node<T>(item);
            if (head == null || tail == null)
            {
                head = node;
                tail = node;
            } 
            else
            {
                tail.next = node;
                node.prev = tail;
                tail = node;
            }

            if (current == null)
                current = node;

            count++;
        }

        public T Current()
        {
            if (current == null)
                throw new InvalidOperationException("Collection is empty");

            return current.data;
        }

        public void Next()
        {
            if (current == null)
                throw new InvalidOperationException("Collection is empty");

            if (current == head && current == tail)
                throw new InvalidOperationException("Collection has only 1 item");

            if (current == tail)
                throw new InvalidOperationException("Cursor points to the end of collection");

            current = current.next;
        }

        public void Prev()
        {
            if (current == null)
                throw new InvalidOperationException("Collection is empty");

            if (current == head && current == tail)
                throw new InvalidOperationException("Collection has only 1 item");

            if (current == head)
                throw new InvalidOperationException("Cursor points to the begin of collection");

            current = current.prev;
        }

        public void Remove(T item)
        {
            if (current == null)
                throw new InvalidOperationException("Collection is empty");

            Node<T>? pointer = head;

            bool itemNotFound = true;

            while (pointer != null)
            {
                if (pointer.data != null &&
                    pointer.data.Equals(item))
                {
                    if (pointer != head && pointer != tail)
                    {
                        pointer.prev.next = pointer.next;
                        pointer.next.prev = pointer.prev;

                        if (current == pointer)
                            current = pointer.next;
                    }
                    else if (pointer == head && pointer == tail)
                    {
                        head = null;
                        tail = null;
                        current = null;
                    }
                    else if (pointer == head)
                    {
                        head = head.next;
                        head.prev = null;

                        if (current == pointer)
                            current = head;
                    }
                    else if (pointer == tail)
                    {
                        tail = tail.prev;
                        tail.next = null;

                        if (current == pointer)
                            current = pointer;
                    }

                    
                    pointer = null;
                    count--;

                    itemNotFound = false;
                } 
                else
                {
                    pointer = pointer.next;
                }
            }

            if (itemNotFound)
                throw new NoExistentElementException("Объект отсутствует в коллекции");
        }

        public T RemoveCurrent()
        {
            if (current == null)
                throw new InvalidOperationException("Collection is empty");

            Node<T> deleted = current;

            if (current != head && current != tail)
            {
                current.prev.next = current.next;
                current.next.prev = current.prev;
                current = current.next;
            }
            else if (current == head && current == tail)
            {
                head = null;
                tail = null;
                current = null;
            }
            else if (current == head)
            {
                head = head.next;
                head.prev = null;
                current = head;
            }
            else if (current == tail)
            {
                tail = tail.prev;
                tail.next = null;
                current = tail;
            }

            count--;
            return deleted.data;
        }

        public void Reset()
        {
            if (current == null)
                throw new InvalidOperationException("Collection is empty");

            current = head;
        }

        public IEnumerator<T> GetEnumerator() => new MyCustomCollectionEnumerator<T>(head);

        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();

        public MyCustomCollection()
        {
            count = 0;
        }

     
    }
}
