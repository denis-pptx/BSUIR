#ifndef DATE_H
#define DATE_H

#include <QApplication>
#include <regex>

class Date {

private:
    int day;
    int month;
    int year;

    int* daysInMonth;

public:
    Date();
    Date(const int, const int, const int);
    Date(const Date&);

    void debug() { qDebug() << day << " " << month << " " << year; }

    Date nextDate();
    Date previousDate();
    bool isLeap() const;
    int weakNumber();
    friend int daysTillYourBithday(const Date&);
    int duration(Date&);

    bool isDateCorrect(QString date);
    bool isLeap(int) const;
    friend int daysFromYearTo(int year, const Date&);
    friend Date toDate(const QString&);
    QString toString();

    Date& operator=(const Date& other);
};

int daysTillYourBithday(const Date&);
Date toDate(const QString&);


#endif // DATE_H
