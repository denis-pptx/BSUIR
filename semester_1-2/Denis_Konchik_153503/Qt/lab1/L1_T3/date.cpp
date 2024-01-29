#include "date.h"
#include <ctime>


Date::Date() {
    this->day = 1;
    this->month = 7;
    this->year = 2004;

    daysInMonth = new int[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
}


Date::Date(const int day, const int month, const int year) {
    this->day = day;
    this->month = month;
    this->year = year;

    daysInMonth = new int[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    daysInMonth[1] = isLeap(year) ? 29 : 28;
}

bool Date::isDateCorrect(QString date) {
    std::regex rx("((0[1-9]|[12][0-9]|3[01])[- /.]"
                 "(0[1-9]|1[012])[- /.]"
                 "([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3}))");

    if (date.length() < 10 || date[2] != '.' || date[5] != '.')
        return false;

    if (!std::regex_match(date.toStdString().c_str(), rx))
        return false;

    QString sday = "";
    for (int i = 0; i < 2; i++) {
        QString tmp = date[i];
        sday += tmp;
    }

    QString smonth = "";
    for (int i = 3; i < 5; i++) {
        QString tmp = date[i];
        smonth += tmp;
    }

    QString syear = "";
    for (int i = 6; i < 10; i++) {
        QString tmp = date[i];
        syear += tmp;
    }

    int iday = sday.toInt();
    int imonth = smonth.toInt();
    int iyear = syear.toInt();

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    daysInMonth[1] = isLeap(iyear) ? 29 : 28;

    if (iday > daysInMonth[imonth - 1])
        return false;

    return true;


}
Date::Date(const Date& date) {
    day = date.day;
    month = date.month;
    year = date.year;

    daysInMonth = new int[12];

    for (int i = 0; i < 12; i++)
        daysInMonth[i] = date.daysInMonth[i];
}

Date Date::nextDate() {

    Date next = *this;
    next.day++;

    if (next.day > next.daysInMonth[month - 1] && month == 12) {
        next.day = 1;
        next.month = 1;
        next.year = next.year + 1;

        next.daysInMonth[1] = next.isLeap() ? 29 : 28;

    } else if (next.day > next.daysInMonth[month - 1]) {
        next.day = 1;
        next.month += 1;
    }

    return next;
}

Date Date::previousDate() {

    Date previous = *this;

    if (previous.day == 1 && previous.month == 1) {
        previous.day = 31;
        previous.month = 12;
        previous.year--;

        previous.daysInMonth[1] = isLeap() ? 29 : 28;

    } else if (previous.day == 1) {
        previous.day = daysInMonth[--previous.month - 1];
    } else {
        previous.day--;
    }

    return previous;
}

bool Date::isLeap() const {
    return !(year % 4 || (!(year % 100) && year % 400));
}

bool Date::isLeap(int year) const {
    return !(year % 4 || (!(year % 100) && year % 400));
}

int Date::weakNumber() {
    int sum = 0;
    for (int i = 0; i < month - 1; i++)
        sum += daysInMonth[i];
    sum += day;

    if (sum % 7 == 0)
        return sum / 7;

    return (sum / 7) + 1;
}

int daysTillYourBithday(const Date& birthDayDate) {

    time_t rawtime;
    tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    Date current(timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);

    int sum = 0;

    if (birthDayDate.month >= current.month) {
        for (int i = current.month - 1; i < birthDayDate.month - 1; i++)
            sum += current.daysInMonth[i];


        sum -= current.day;
        sum += birthDayDate.day;

    } else {
        for (int i = current.month - 1; i < 12; i++)
            sum += current.daysInMonth[i];
        sum-= current.day;

        for (int i = 0; i < birthDayDate.month - 1; i++)
            sum += current.daysInMonth[i];
        sum += birthDayDate.day;
    }

    if (sum < 0) sum = 365 - sum;

    return sum;
}

int Date::duration(Date& date) {


    int leastYear = year <= date.year ? year : date.year;

    int daysCurrentDate = daysFromYearTo(leastYear, *this);
    int daysNextDate = daysFromYearTo(leastYear, date);

    return abs(daysCurrentDate - daysNextDate);
}

int daysFromYearTo(int year, const Date& date) {

    int sum = 0;

    for (int i = year; i < date.year; i++)
        sum += date.isLeap(i) ? 366 : 365;


    for (int i = 0; i < date.month - 1; i++) {
        sum += date.daysInMonth[i];
    }

    sum += date.day;

    return sum;
}

Date toDate(const QString& line) {

    int i = 0;

    QString day = "";
    while(line[i] != '.')
        day += line[i++];
    i++;


    QString month = "";
    while(line[i] != '.')
        month += line[i++];
    i++;

    QString year = "";
    while(i < line.size())
        year += line[i++];

    Date date(day.toInt(), month.toInt(), year.toInt());
    return date;
}

QString Date::toString() {

    QString line = "";

    line += day > 9 ? QString::number(day) + "." : "0" + QString::number(day) + ".";
    line += month > 9 ? QString::number(month) + "." : "0" + QString::number(month) + ".";

    for (int i = 0; i < 4 - QString::number(year).size(); i++)
        line += "0";
    line += QString::number(year);

    return line;
}

Date& Date::operator=(const Date& other) {
    day = other.day;
    month = other.month;
    year = other.year;

    daysInMonth = new int[12];

    for (int i = 0; i < 12; i++)
        daysInMonth[i] = other.daysInMonth[i];

    return *this;
}
