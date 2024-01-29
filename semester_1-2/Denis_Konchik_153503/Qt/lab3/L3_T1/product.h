#ifndef PRODUCT_H
#define PRODUCT_H

#include <QDate>

class Product
{
private:
    char identifer[5] = "!@#$";

    char m_name[101];
    int m_amount;
    double m_price;
    QDate m_date;

    enum Columns { Name, Amount, Price, Date };

public:
    Product() {
        m_name[0] = '\0';
        m_amount = 0;
        m_price = 0;
        m_date = QDate(1, 1, 1);
    }

    Product(QString name, int amount, double price, QDate date)
        : m_amount(amount), m_price(price), m_date(date)
    {
        setName(name);
    }

    QString getName() const { return QString(m_name); }
    void setName(QString name) {
        int i = 0;
        for (; i < name.size() && i < 100; i++)
            m_name[i] = name[i].toLatin1();
        m_name[i] = '\0';
    }

    int getAmount() const { return m_amount; }
    void setAmount(int amount) { m_amount = amount;}

    double getPrice() const { return m_price; }
    void setPrice(double price) { m_price = price; }

    QDate getDate() const { return m_date; }
    void setDate(QDate date) { m_date = date; }


    QString getColumnByIndex(int column)
    {
        Columns column_ = static_cast<Columns>(column);

        switch (column_){
        case Name:
            return getName();
            break;
        case Amount:
            return QString::number(getAmount());
            break;
        case Price:
            return QString::number(getPrice());
            break;
        case Date:
            return getDate().toString("dd.MM.yyyy");
            break;
        default:
            return "error";
        }

    }


    bool isValidParse() {

        if (identifer[0] == '!' &&
                identifer[1] == '@' &&
                identifer[2] == '#' &&
                identifer[3] == '$')
            return true;

        return false;
    }
 };

#endif // PRODUCT_H
