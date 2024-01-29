#ifndef COMPANY_H
#define COMPANY_H
#include <QString>

struct Company {
    char identify = '@';
    char name[100] = "null";
    char speciality[100] = "null";
    char post[100] = "null";
    int salary = 0;
    int vacationDays = 0;
    bool isNeedHigherEducation = 0;
    int minAge = 0;
    int maxAge = 0;
};


#endif // COMPANY_H
