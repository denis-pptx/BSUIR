#ifndef ENROLLEE_H
#define ENROLLEE_H

#include <QString>

class Enrollee
{
private:
    char identifer[5] = "&^%*";

    char m_surname[101];
    char m_name[101];
    char m_patronymic[101];
    char m_city[101];
    int m_score;


    enum Columns { Surname, Name, Patronymic, City, Score };

public:
    Enrollee() {
        m_surname[0] =      '\0';
        m_name[0] =         '\0';
        m_patronymic[0] =   '\0';
        m_city[0] =         '\0';

        m_score = 0;
    }

    Enrollee(QString surname, QString name, QString patronymic, QString city, int score)
        : m_score(score)
    {
        setSurname(surname);
        setName(name);
        setPatronymic(patronymic);
        setCity(city);
    }

    QString getSurname() const { return QString(m_surname); }
    void setSurname(QString surname) {
        int i = 0;
        for (; i < surname.size() && i < 100; i++)
            m_surname[i] = surname[i].toLatin1();
        m_surname[i] = '\0';
    }

    QString getName() const { return QString(m_name); }
    void setName(QString name) {
        int i = 0;
        for (; i < name.size() && i < 100; i++)
            m_name[i] = name[i].toLatin1();
        m_name[i] = '\0';
    }

    QString getPatronymic() const { return QString(m_patronymic); }
    void setPatronymic(QString patronymic) {
        int i = 0;
        for (; i < patronymic.size() && i < 100; i++)
            m_patronymic[i] = patronymic[i].toLatin1();
        m_patronymic[i] = '\0';
    }

    QString getCity() const { return QString(m_city); }
    void setCity(QString city) {
        int i = 0;
        for (; i < city.size() && i < 100; i++)
            m_city[i] = city[i].toLatin1();
        m_city[i] = '\0';
    }

    void setScore(int score) { m_score = score; }
    int getScore() const { return m_score; }


    QString getColumnByIndex(int column)
    {
        Columns column_ = static_cast<Columns>(column);

        switch (column_){
        case Surname:
            return getSurname();
            break;
        case Name:
            return getName();
            break;
        case Patronymic:
            return getPatronymic();
            break;
        case City:
            return getCity();
            break;
        case Score:
            return QString::number(getScore());
            break;
        default:
            return "error";
        }

    }


    bool isValidParse() {

        if (identifer[0] == '&' &&
                identifer[1] == '^' &&
                identifer[2] == '%' &&
                identifer[3] == '*')
            return true;

        return false;
    }
 };


#endif // ENROLLEE_H
