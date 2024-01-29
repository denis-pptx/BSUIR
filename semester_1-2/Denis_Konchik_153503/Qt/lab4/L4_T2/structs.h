#ifndef STRUCTS_H
#define STRUCTS_H

#include "my_string.h"
using namespace my_string;

// Координата слова (ряд, столбец)
struct Coords {
    int row;
    int column;

    Coords(int row, int column) {
        this->row = row;
        this->column = column;
    }


    Coords() {
        row = 0;
        column = 0;
    }
};

// Прототип функции (имя функции, прототип)
struct Prototype {
    string funcName;
    string prototype;

    Prototype(string funcName, string prototype) {
        this->funcName = funcName;
        this->prototype = prototype;
    }

    Prototype() {
        funcName = "";
        prototype = "";
    }
};

#endif // STRUCTS_H
