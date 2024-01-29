#ifndef HASH_H
#define HASH_H

#include <list>
#include <cmath>
using namespace std;

namespace my_hash {

    template<class T1, class T2, class HashFunctor>
    class unordered_map {
    protected:
        list<pair<const T1, T2>>* arr;
        int arr_size;
        int N;

        int getHash(const T1 key) {
            HashFunctor hashFunctor;
            double temp = hashFunctor(key) * 0.618033;
            temp = fabs(temp - (int)temp);
            return (int)(arr_size * temp);
        }

    public:
        unordered_map(int arr_size) {
            this->arr_size = arr_size;
            arr = new list<pair<const T1, T2>>[arr_size];
            N = 0;
        }

        ~unordered_map() {
            clear();
            delete[] arr;
        }

        void clear() {
            for (int i = 0; i < arr_size; i++)
                arr[i].clear();

            N = 0;
        }

        pair<const T1, T2>* search(const T1& key) {
            int hash = getHash(key);

            for (auto& it : arr[hash])
                if (it.first == key)
                    return &it;

            return nullptr;
        }

        bool contains(const T1& key) {
            return search(key) ? true : false;
        }

        void insert(pair<const T1, T2> item) {
            int hash = getHash(item.first);

            if (!search(item.first)) {
                arr[hash].push_back(item);
                ++N;
            }
        }

        void erase(const T1& key) {
            int hash = getHash(key);

            for (typename list<pair<const T1, T2>>::iterator it = arr[hash].begin(); it != arr[hash].end(); ++it) {
                if ((*it).first == key) {
                    arr[hash].erase(it);
                    --N;
                    return;
                }
            }
        }

        T2& operator[](const T1& first) {

            insert(make_pair(first, T2()));

            return search(first)->second;
        }

        T2 operator[](const T1& first) const {

            insert(make_pair(first, T2()));

            return search(first)->second;
        }





        int get_arr_size() {
            return arr_size;
        }

        int get_N() {
            return N;
        }

        list<pair<const T1, T2>>* get_arr() {
            return arr;
        }


    };

}

#endif // HASH_H
