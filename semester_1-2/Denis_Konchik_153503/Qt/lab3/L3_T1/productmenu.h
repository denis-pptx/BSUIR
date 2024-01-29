#ifndef PRODUCTMENU_H
#define PRODUCTMENU_H

#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFile>
#include <QDate>
#include "node_list.h"
#include "product.h"

class ProductMenu : public QDialog
{
    Q_OBJECT
protected:

    QLineEdit* lineName;
    QSpinBox* boxAmount;
    QDoubleSpinBox* boxPrice;
    QDateEdit* boxDate;

    QGridLayout* lay;
    QPushButton* Ok;
    QPushButton* Cancel;



public:

    ProductMenu()
        : lineName(new QLineEdit), boxAmount(new QSpinBox),
          boxPrice(new QDoubleSpinBox), boxDate(new QDateEdit), lay(new QGridLayout)
    {
        setWindowFlags(Qt::Window | Qt::Tool);
        setModal(true);
        lay->addWidget(new QLabel("Наименование: "), 0, 0);
        lay->addWidget(lineName, 0, 1);
        lineName->setMaxLength(100);
        lineName->setValidator(new QRegularExpressionValidator(QRegularExpression("^[^а-яА-ЯёЁ]+$"), this));

        lay->addWidget(new QLabel("Количество: "), 1, 0);
        lay->addWidget(boxAmount, 1, 1);
        boxAmount->setRange(0, 1000000);

        lay->addWidget(new QLabel("Цена: "), 2, 0);
        lay->addWidget(boxPrice, 2, 1);
        boxPrice->setRange(0, 1000000);

        lay->addWidget(new QLabel("Дата поступления: "), 3, 0);
        lay->addWidget(boxDate, 3, 1);
        boxDate->setDateRange(QDate(1,1,1), QDate::currentDate());
        boxDate->setDate(QDate::currentDate());

        Ok = new QPushButton("&Ок");
        lay->addWidget(Ok, 4, 0);

        Cancel = new QPushButton("&Отмена");

        setLayout(lay);
    }

    QString getName() { return lineName->text(); }
    int getAmount() { return boxAmount->value(); }
    double getPrice() { return boxPrice->value(); }
    QDate getDate() { return boxDate->date(); }
};

class ProductMenuAdd : public ProductMenu
{
    Q_OBJECT

public:
    ProductMenuAdd() {

        setWindowTitle("Добавить товар");

        lay->addWidget(Cancel, 4, 1);

        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
    }

    void activate() {

        lineName->setText("");
        boxAmount->setValue(0);
        boxPrice->setValue(0);
        boxDate->setDate(QDate::currentDate());

        show();
        activateWindow();
    }
};


class ProductMenuEdit : public ProductMenu
{
    Q_OBJECT

public:
    ProductMenuEdit() {
        setWindowTitle("Изменить товар");

        lay->addWidget(Cancel, 4, 1);

        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
    }

    void activate(node_list::list<Product>::iterator it) {

        lineName->setText((*it).getName());
        boxAmount->setValue((*it).getAmount());
        boxPrice->setValue((*it).getPrice());
        boxDate->setDate(((*it).getDate()));

        show();
        activateWindow();
    }

};

//class ProductMenuView : public ProductMenu
//{
//    Q_OBJECT

//public:
//    ProductMenuView() {
//        setWindowTitle("Информация о товаре");

//        lineName->setReadOnly(true);
//        boxAmount->setReadOnly(true);
//        boxPrice->setReadOnly(true);
//        boxDate->setReadOnly(true);

//        boxAmount->setButtonSymbols(QAbstractSpinBox::NoButtons);
//        boxPrice->setButtonSymbols(QAbstractSpinBox::NoButtons);
//        boxDate->setButtonSymbols(QAbstractSpinBox::NoButtons);

//        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));

//    }

//    void activate(node_list::list<Product>::iterator it) {


//        lineName->setText((*it).getName());
//        boxAmount->setValue((*it).getAmount());
//        boxPrice->setValue((*it).getPrice());
//        boxDate->setDate(((*it).getDate()));

//        show();
//        activateWindow();
//    }
//};

#endif // PRODUCTMENU_H
