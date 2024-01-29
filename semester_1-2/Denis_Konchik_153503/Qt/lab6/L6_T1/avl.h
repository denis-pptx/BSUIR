#ifndef AVL_H
#define AVL_H

#include <QDebug>
#include <QTableView>
#include <QStandardItemModel>
#include "item.h"
#include <iostream>
#include <queue>

// Узел дерева
template<class T>
struct Node {

    T item;
    int height;
    Node* left;
    Node* right;

    Node(T item) {
        this->item = item;
        left = right = nullptr;
        height = 1;
    }
};

template<class T>
class Tree {
protected:


    // Высота узла
    int height(Node<T>* p) {
        if (p)
            return p->height;
        else
            return 0;
    }

    // Разница между высотой правого и левого сына
    int bfactor(Node<T>* p) {
        return height(p->right) - height(p->left);
    }

    // Пофиксить высоту узла
    void fixheight(Node<T>* p) {
        int hl = height(p->left);
        int hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    // Правый поворот вокруг узла
    Node<T>* rotateright(Node<T>* p)  {
        Node<T>* l = p->left;
        p->left = l->right;
        l->right = p;

        fixheight(p);
        fixheight(l);

        return l;
    }

    // Левый поворот вокруг узла
    Node<T>* rotateleft(Node<T>* p)  {
        Node<T>* r = p->right;
        p->right = r->left;
        r->left = p;

        fixheight(p);
        fixheight(r);

        return r;
    }

    // Балансировка узла
    Node<T>* balance(Node<T>* p)
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


    // Поиск узла с минимальным ключом в дереве p
    Node<T>* findmin(Node<T>* p)
    {
        if (p->left)
            return findmin(p->left);
        else
            return p;
    }

    // Удаление узла с минимальным ключом из дерева p
    Node<T>* removemin(Node<T>* p)
    {
        if(!p->left)
            return p->right;

        p->left = removemin(p->left);

        return balance(p);
    }



    // Вставка item в дерево p
    Node<T>* insert(Node<T>* p, T item)
    {
        if (!p)
            return new Node(item);

        if (item < p->item)
            p->left = insert(p->left, item);
        else
            p->right = insert(p->right, item);

        return balance(p);
    }

    // Удаление item из дерева p
    Node<T>* remove(Node<T>* p, T item) {

        if(!p)
            return p;

        if (item < p->item)
            p->left = remove(p->left, item);
        else if (item > p->item)
            p->right = remove(p->right, item);
        else {

            Node<T>* l = p->left;
            Node<T>* r = p->right;

            delete p;
            size--;

            if (!r)
                return l;

            Node<T>* min = findmin(r);

            min->right = removemin(r);
            min->left = l;

            return balance(min);
        }

        return balance(p);
    }

    // Поиск item в дереве p
    Node<T>* searchNode(Node<T>* p, T item) {
        Node<T>* curr = p;

        while (curr && curr->item != item) {
            if (curr->item > item)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return curr;
    }

    // Удалить дерево
    void delete_tree(Node<T>* curr) {
        if (curr) {
            delete_tree(curr->left);
            delete_tree(curr->right);
            delete curr;
        }
    }

    Node<T>* head;
    int size;
public:
    Tree() {
        head = nullptr;
        size = 0;
    }

    ~Tree() {
        clear();
    }

    void push(T item) {
        if (!searchNode(head, item)) {
             head = insert(head, item);
             size++;
        }
    }

    void pop(T item) {
        head = remove(head, item);
    }

    Node<T>* search(T item) {
        return searchNode(head, item);
    }

    void clear() {
        delete_tree(head);
        head = nullptr;
        size = 0;
    }


};

template<class T>
class TreeMod : public Tree<T> {
private:
    QStandardItemModel* model;
    QTableView* view;

    QVector<Item> items;


    void direct(Node<T>* p) {

        if (p) {
            items.push_back(p->item);
            direct(p->left);
            direct(p->right);
        }
    }

    void symmetrical(Node<T>* p) {
        if (p) {
            symmetrical(p->left);
            items.push_back(p->item);
            symmetrical(p->right);
        }
    }

    void back(Node<T>* p) {
        if (p) {
            back(p->left);
            back(p->right);
            items.push_back(p->item);
        }
    }

    void width(Node<T>* p) {

        std::queue<Node<T>*> queue;
        queue.push(p);

        while (!queue.empty()) {
            Node<T>* node = queue.front();
            queue.pop();

            items.push_back(node->item);

            if (node->left)
                queue.push(node->left);

            if (node->right)
                queue.push(node->right);
        }
    }

    void printNode(Node<T>* node, size_t level = 0){

        if (node != nullptr) {
            printNode(node->right, level + 1);

            std::cout << '\n';

            if (node == Tree<T>::head)
               std::cout << "root -> ";
            else
               std::cout << "          ";

            for (size_t i = 0; i < level && node != Tree<T>::head; i++)
                std::cout << "      ";

            std::cout << node->item.key << "(" << node->height << ")";

            printNode(node->left, level + 1);
        }
    }


public:

    TreeMod() {
        model = new QStandardItemModel();
        view = new QTableView();
    }


    void directBypass() {
        view->setWindowTitle("Прямой");
        items.clear();
        direct(Tree<T>::head);
    }

    void symmetricalBypass() {
        view->setWindowTitle("Симметричный");
        items.clear();
        symmetrical(Tree<T>::head);
    }

    void backBypass() {
        view->setWindowTitle("Обратный");
        items.clear();
        back(Tree<T>::head);
    }

    void widthBypass() {
        view->setWindowTitle("В ширину");
        items.clear();
        width(Tree<T>::head);
    }

    void bypass() {

        delete model;
        model = new QStandardItemModel(items.size(), 2);

        model->setHeaderData(0, Qt::Horizontal, "Ключ");
        model->setHeaderData(1, Qt::Horizontal, "Текст");

        view->setModel(model);

        for (int row = 0; row < items.size(); row++) {

            QModelIndex index = model->index(row, 0);
            model->setData(index, items[row].key);
            model->item(index.row(), index.column())->setEditable(false);

            index = model->index(row, 1);
            model->setData(index, items[row].str);
            model->item(index.row(), index.column())->setEditable(false);
        }

        view->show();
        view->activateWindow();
        view->setFixedSize(view->size());

    }

    void show() {
        system("cls");
        printNode(Tree<T>::head);
    }

    Item middle(bool& found) {
        items.clear();
        symmetrical(Tree<Item>::head);

        if (items.empty()) {
            found = false;
            return Item();
        }

        double mid = (items.front().key + items.back().key) / 2.0;
        Item ret = items[0];
        double diff = fabs(ret.key - mid);

        for (int i = 0; i < items.size(); i++) {
            double diff_tmp = fabs(items[i].key - mid);
            if (diff_tmp < diff) {
                diff = diff_tmp;
                ret = items[i];
            }
        }

        return ret;
    }



};


#endif // AVL_H
