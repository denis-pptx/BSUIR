#ifndef WORKER_H
#define WORKER_H

#include <QString>

struct Worker {
    char identify = '#';
    char name[100] = "null";
    int age = 0;
    char speciality[100] = "null";
    bool hasHigherEducation = 0;
    char post[100] = "null";
    int minSalary = 0;
};


#endif // WORKER_H
