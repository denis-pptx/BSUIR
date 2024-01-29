#ifndef MAP_H
#define MAP_H


#include <iostream>
#include <string>
#include <QDebug>
using namespace std;

namespace my_map {

    template<class T1, class T2>
    struct Node {

        pair<const T1, T2> item;
        int height;
        Node* left;
        Node* right;
        Node* parent;

        Node(pair<const T1, T2> item_) : item(item_) {
            parent = left = right = nullptr;
            height = 1;
        }
    };

    template<class T1, class T2>
    class Tree {
    protected:

        int height(Node<const T1, T2>* p) {
            if (p)
                return p->height;
            else
                return 0;
        }

        int bfactor(Node<const T1, T2>* p) {
            return height(p->right) - height(p->left);
        }

        void fixheight(Node<const T1, T2>* p) {
            int hl = height(p->left);
            int hr = height(p->right);
            p->height = (hl > hr ? hl : hr) + 1;
        }

        Node<const T1, T2>* rotateright(Node<const T1, T2>* p) {
            Node<const T1, T2>* l = p->left;

            l->parent = p->parent;

            p->left = l->right;
            if (l->right)
                l->right->parent = p;

            l->right = p;
            if (p)
                p->parent = l;


            fixheight(p);
            fixheight(l);

            return l;
        }

        Node<const T1, T2>* rotateleft(Node<const T1, T2>* p) {
            Node<const T1, T2>* r = p->right;

            r->parent = p->parent;

            p->right = r->left;
            if (r->left)
                r->left->parent = p;

            r->left = p;
            if (p)
                p->parent = r;

            fixheight(p);
            fixheight(r);

            return r;
        }

        Node<const T1, T2>* balance(Node<const T1, T2>* p)
        {
            fixheight(p);

            if (bfactor(p) == 2) {

                if (bfactor(p->right) < 0)
                    p->right = rotateright(p->right);

                return rotateleft(p);
            }

            if (bfactor(p) == -2) {

                if (bfactor(p->left) > 0)
                    p->left = rotateleft(p->left);

                return rotateright(p);
            }
            return p;
        }

        Node<const T1, T2>* findmin(Node<const T1, T2>* p)
        {
            if (p->left)
                return findmin(p->left);
            else
                return p;
        }

        Node<const T1, T2>* removemin(Node<const T1, T2>* p)
        {
            if (!p->left)
                return p->right;

            p->left = removemin(p->left);
            if (p->left)
                p->left->parent = p;

            return balance(p);
        }

        Node<const T1, T2>* insert(Node<const T1, T2>* p, pair<const T1, T2> item)
        {
            if (!p)
                return new Node<const T1, T2>(item);

            if (item.first < p->item.first) {
                p->left = insert(p->left, item);
                p->left->parent = p;
            }
            else {
                p->right = insert(p->right, item);
                p->right->parent = p;
            }

            return balance(p);
        }

        Node<const T1, T2>* remove(Node<const T1, T2>* p, const T1& key) {

            if (!p)
                return p;

            if (key < p->item.first)
                p->left = remove(p->left, key);
            else if (key > p->item.first)
                p->right = remove(p->right, key);
            else {

                Node<const T1, T2>* l = p->left;
                Node<const T1, T2>* r = p->right;
                Node<const T1, T2>* prnt = p->parent;

                delete p;
                size--;

                if (!r) {
                    if (l)
                        l->parent = prnt;
                    return l;
                }


                Node<const T1, T2>* min = findmin(r);
                if (min)
                    min->parent = prnt;

                Node<const T1, T2>* right_removed_min = removemin(r);
                if (right_removed_min)
                    right_removed_min->parent = min;
                if (min)
                    min->right = right_removed_min;

                if (l)
                    l->parent = min;
                if (min)
                    min->left = l;

                return balance(min);
            }

            return balance(p);
        }

        Node<const T1, T2>* searchNode(Node<const T1, T2>* p, const T1& key) {
            Node<const T1, T2>* curr = p;

            while (curr && curr->item.first != key) {

                if (curr->item.first > key)
                    curr = curr->left;
                else
                    curr = curr->right;
            }

            return curr;
        }

        void delete_tree(Node<const T1, T2>* curr) {
            if (curr) {
                delete_tree(curr->left);
                delete_tree(curr->right);
                delete curr;
            }
        }

        void printNode(Node<const T1, T2>* node, size_t level = 0) {

            if (node != nullptr) {
                printNode(node->right, level + 1);

                std::cout << '\n';

                if (node == Tree<T1, T2>::root)
                    std::cout << "root -> ";
                else
                    std::cout << "          ";

                for (size_t i = 0; i < level && node != Tree<T1, T2>::root; i++)
                    std::cout << "      ";

               /* std::cout << node->item.first << "(";
                if (node->parent)
                    std::cout << node->parent->item.first << ")";
                else
                    std::cout << "-)";*/
                std::cout << node->item.first.toStdString() << "(" << node->item.second.toStdString() << ")";

                printNode(node->left, level + 1);
            }
        }

        Node<const T1, T2>* root;
        int size;

    public:

        Tree() {
            root = nullptr;
            size = 0;
        }

        ~Tree() {
            clear();
        }

        void clear() {
            delete_tree(root);
            root = nullptr;
            size = 0;
        }

        void print() {
            system("cls");
            printNode(root);
        }

    protected:

        void push(pair<const T1, T2> item) {
            if (!searchNode(root, item.first)) {
                root = insert(root, item);
                size++;
            }
        }

        void pop(const T1& key) {
            root = remove(root, key);
        }

        Node<const T1, T2>* search(const T1& key) {
            return searchNode(root, key);
        }

    };

    template<class T1, class T2>
    class map : public Tree<T1, T2> {
    private:
        list<Node<const T1, T2>*> lst;

        void symmetrical(Node<const T1, T2>* node) {
            if (node) {
                symmetrical(node->left);
                lst.push_back(node);
                symmetrical(node->right);
            }
        }

    public:

        class it_list {
        private:
            list<Node<const T1, T2>*> lst;
            typename list<Node<const T1, T2>*>::iterator it;
        public:

            it_list(const list<Node<const T1, T2>*>& other, bool begin = true) {
                lst = other;

                if (begin)
                    it = lst.begin();
                else
                    it = lst.end();
            }

            it_list(const it_list& other) {
                *this = other;
            }

            pair<const T1, T2>& operator*() {
                return (*it)->item;
            }

            it_list& operator++() {
                ++it;
                return *this;
            }

            it_list& operator--() {
                --it;
                return *this;
            }

        };

        it_list begin_l() {
            lst.clear();
            symmetrical(Tree<T1, T2>::root);
            return it_list(lst);
        }

        it_list end_l() {
            lst.clear();
            symmetrical(Tree<T1, T2>::root);
            return it_list(lst, false);

        }



        class iterator {
        private:
            Node<const T1, T2>* node;
            Node<const T1, T2>* root;

        public:

            iterator(Node<const T1, T2>* node_ = nullptr, Node<const T1, T2>* root_ = nullptr)
                : node(node_), root(root_) {

            }

            iterator& operator=(const iterator& other) {
                node = other.node;
                root = other.root;

                return *this;
            }

            pair<const T1, T2>& operator*() {
                return node->item;
            }

            iterator& operator++() {

                // Стать в мин
                if (!node) {

                    if (!root)
                        return *this;

                    node = root;

                    while (node->left != nullptr) {
                        node = node->left;
                    }

                    return *this;
                }

                // Если правое поддерево не ноль,
                // найти в нем самый левый узел
                if (node->right != nullptr) {

                    node = node->right;

                    while (node->left != nullptr) {
                        node = node->left;
                    }
                }
                // Иначе найти узел, для которого
                // node - левый потомок
                else {
                    Node<const T1, T2>* p = node->parent;
                    while (p != nullptr && node == p->right) {
                        node = p;
                        p = p->parent;
                    }

                    node = p;
                }

                return *this;
            }

            iterator& operator--() {

                // Стать в макс
                if (!node) {

                    if (!root)
                        return *this;

                    node = root;

                    while (node->right != nullptr)
                        node = node->right;

                    return *this;
                }

                // Если левое поддерево не ноль,
                // найти в нем самый правый узел
                if (node->left != nullptr) {

                    node = node->left;

                    while (node->right != nullptr) {
                        node = node->right;
                    }
                }
                // Иначе найти узел, для которого
                // node - правый потомок
                else {
                    Node<const T1, T2>* p = node->parent;
                    while (p != nullptr && node == p->left) {
                        node = p;
                        p = p->parent;
                    }

                    node = p;
                }

                return *this;
            }

            iterator& operator+(int n) {

                for (int i = 0; i < n; i++)
                    operator++();

                return *this;
            }

            iterator& operator-(int n) {

                for (int i = 0; i < n; i++)
                    operator--();

                return *this;
            }

            bool operator==(const iterator& other) {
                return node == other.node;
            }

            bool operator!=(const iterator& other) {
                return node != other.node;
            }
        };

        T2& operator[](const T1& first) {

            Tree<T1, T2>::push(make_pair(first, T2()));

            return Tree<T1, T2>::search(first)->item.second;
        }

        iterator insert(pair<const T1, T2> item) {
            Tree<T1, T2>::push(item);
            return iterator(Tree<T1, T2>::root);
        }

        iterator erase(const T1& key) {
            Tree<T1, T2>::pop(key);
            return iterator(Tree<T1, T2>::root);
        }

        int count(const T1& first) {
            return Tree<T1, T2>::search(make_pair(first, NULL)) ? 1 : 0;
        }

        iterator find(const T1& key) {
            Node<const T1, T2>* node = Tree<T1, T2>::search(key);

            if (node)
                return iterator(node, Tree<T1, T2>::root);
            else
                return end();
        }

        iterator begin() {
            return end() + 1;
        }

        iterator end() {
            return iterator(nullptr, Tree<T1, T2>::root);
        }

    };

}
#endif // MAP_H
