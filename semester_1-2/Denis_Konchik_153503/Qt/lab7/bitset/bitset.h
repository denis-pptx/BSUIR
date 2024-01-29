#ifndef BITSET_H
#define BITSET_H


#include <QString>
#include <cmath>
#include <QDebug>

#define bit (sizeof(size_t) * 8)

template<size_t N>
class bitset {
private:

    size_t bits[N / bit + 1];

    bool get_bit(size_t n) {
        if (n >= N)
            return false;

        return ((bits[n / bit] & ((size_t)1 << (n % bit))));
    }

    void set_bit(size_t n, bool b) {
        if (n >= N)
            return;

        if (b)
            bits[n / bit] |= ((size_t)1 << (n % bit));
        else
            bits[n / bit] &= ~((size_t)1 << (n % bit));


    }

    struct BitReference {
        size_t* ptr;
        size_t pos;

        BitReference& operator=(bool b) {
            if (b)
                *ptr |= ((size_t)1 << pos);
            else
                *ptr &= ~((size_t)1 << pos);

            return *this;
        }

        operator bool() {
            return *ptr & ((size_t)1 << pos);
        }
    };

public:

    bitset() {
        reset();
    }

    bitset(unsigned long long number) {
        reset();
        size_t i = 0;

        while (number) {
            set_bit(i, number % 2);
            number /= 2;
            i++;
        }
    }

    bitset(QString str) {
        reset();
        for (size_t i = 0; i < str.size(); i++)
            set_bit(i, str[i].toLatin1() - '0');
    }


    // Сбросить все биты
    void reset() {

        for (size_t i = 0; i < N / bit + 1; i++)
            bits[i] = 0;

        for (size_t i = 0; i < N; i++)
            set_bit(i, false);
    }

    // Сбросить бит в позиции
    void reset(size_t n) {
        set_bit(n, false);
    }

    // Установить все биты
    void set() {
        for (size_t i = 0; i < N; ++i)
            set_bit(i, true);
    }

    // Установить бит в позиции
    void set(size_t n) {
        set_bit(n, true);
    }

    // Инвертировать все биты
    void flip() {
        for (size_t i = 0; i < N; i++)
            if (get_bit(i))
                set_bit(i, false);
            else
                set_bit(i, true);
    }

    // Инвертировать бит в позиции
    void flip(size_t n) {
        if (get_bit(n))
            set_bit(n, false);
        else
            set_bit(n, true);

    }

    // Присвоено ли значение в позиции
    bool test(size_t n) {
        return get_bit(n);
    }

    // Есть ли хотя бы у одного бита значение
    bool any() {
        for (size_t i = 0; i < N; i++)
            if (get_bit(i))
                return true;

        return false;
    }

    // Все ли биты не заданы
    bool none() {
        return !any();
    }

    // Все ли биты заданы
    bool all() {
        bool ALL = true;

        for (size_t i = 0; i < N && ALL; i++)
            if (!get_bit(i))
                ALL = false;

        return ALL;
    }

    // Сколько битов задано
    size_t count() {
        size_t c = 0;
        for (size_t i = 0; i < N; i++)
            if (get_bit(i))
                c++;

        return c;
    }


    // Число битов
    size_t size() {
        return N;
    }


    BitReference operator[] (size_t n) {
        size_t pos = n % bit;
        size_t* ptr = bits + n / bit;

        return BitReference{ptr, pos};
    }

    QString to_string() {

        QString str;

        for (size_t i = 0; i < N; i++) {
            str.push_back(QString::number(this->operator[](N - i - 1)));
        }

        return str;
    }

    unsigned long to_ulong() {

        if (N > sizeof(unsigned long) * 8)
            throw std::overflow_error("");

        unsigned long number = 0;

        for (size_t i = 0; i < N; ++i)
            number += get_bit(i) * pow(2, i);

        return number;

    }

    unsigned long long to_ullong() {

        if (N > sizeof(unsigned long long) * 8)
            throw std::overflow_error("");

        unsigned long long number = 0;

        for (size_t i = 0; i < N; ++i)
            number += get_bit(i) * pow(2, i);

        return number;
    }



};

#endif // BITSET_H
