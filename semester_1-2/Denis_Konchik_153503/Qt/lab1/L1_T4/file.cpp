#include "file.h"

template<class T>
T* fileParse(T* arr, QString filename, int& N) {

    QFile file;
    file.setFileName(filename);

    if (file.open(QIODevice::ReadOnly)) {

        N = 0; free(arr); arr = nullptr;
        T Parse;

        while (file.read((char*)&Parse, sizeof(T))) {
            arr = (T*)realloc(arr, ++N * sizeof(T));
            arr[N - 1] = Parse;
        }


        //qDebug() << "Loaded from " << filename << " : " << N;

    } else {
        qDebug() << "BAD OPEN";
    }

    file.close();

    return arr;
}

template<class T>
void fileRewrite(T* arr, QString filename, int& N) {
    QFile file;
    file.setFileName(filename);

    if (file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {

        for (int i = 0; i < N; i++)
            file.write((char*)&arr[i], sizeof(T));

        //qDebug() << "Rewrited" << filename;

    } else {
        qDebug() << "BAD OPEN";
    }

    file.close();
}
