#ifndef ITEM_H
#define ITEM_H

#include <QString>

struct Item {
    int key;
    QString str;

    bool operator<(const Item& other) {
        return key < other.key;
    }

    bool operator<=(const Item& other) {
        return key <= other.key;
    }

    bool operator>(const Item& other) {
        return key > other.key;
    }

    bool operator>=(const Item& other) {
        return key >= other.key;
    }

    bool operator==(const Item& other) {
        return key == other.key;
    }

    bool operator!=(const Item& other) {
        return key != other.key;
    }

    Item() {
        key = 0;
        str = "";
    }

    Item(int key, QString str) {
        this->key = key;
        this->str = str;
    }
};

#endif // ITEM_H
