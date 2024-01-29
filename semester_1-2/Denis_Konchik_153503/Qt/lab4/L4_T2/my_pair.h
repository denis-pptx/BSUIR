#ifndef MY_PAIR_H
#define MY_PAIR_H

#include <iostream>

namespace my_pair {

    template<class T1, class T2>
    struct pair {
        T1 first;
        T2 second;

        pair() { }

        pair(const T1& x, const T2& y)
            : first(x),second(y) { }

        pair(T1&& x, T2&& y)
            : first(x),second(y) { }


        pair(const pair<T1, T2>& p)
            : first(p.first), second(p.second) { }

        pair(pair<T1, T2>&& p)
            : first(p.first), second(p.second) { }

        pair<T1, T2>& operator=(const pair<T1, T2>& p) {
            first = p.first;
            second = p.second;
            return *this;
        }

        pair<T1, T2>& operator=(pair<T1, T2>&& p) {
            first = p.first;
            second = p.second;
            return *this;
        }


        void swap(pair<T1, T2>& p) {
            std::swap(first, p.first);
            std::swap(second, p.second);
        }

        bool operator==(const pair<T1, T2>& p) {
            return first == p.first && second == p.second;
        }

    };

    template<class T1, class T2>
    pair<T1, T2> make_pair(const T1& x, const T2& y) {
        return pair<T1, T2>(x, y);
    }


}

#endif // MY_PAIR_H
