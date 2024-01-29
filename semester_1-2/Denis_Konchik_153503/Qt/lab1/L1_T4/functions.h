#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>

struct Company;
struct Worker;

void copy(char* first, QString second) {
    int i = 0;
    for (; i < second.size(); i++)
        first[i] = second[i].toLatin1();
    first[i] = '\0';
}

bool compare(const char* first, const char* second) {
    if (first[0] == '\0' && second[0] == '\0')
        return false;

    int i = 0;
    while(first[i] != '\0' || second[i] != '\0') {
        if (first[i] != second[i++])
            return false;
    }
    return true;
}

bool strToBool(const QString str) {
    return str == "YES" ? 1 : 0;
}

QString boolToStr(const bool val) {
    return val ? "YES" : "NO";
}


bool isSuitable(const Company& company, const Worker& worker) {

    if (company.isNeedHigherEducation && !worker.hasHigherEducation)
        return false;


    return compare(company.speciality, worker.speciality);
            company.minAge <= worker.age && company.maxAge >= worker.age &&
            company.salary >= worker.minSalary &&
            compare(company.post, worker.post);
}

#endif // FUNCTIONS_H
