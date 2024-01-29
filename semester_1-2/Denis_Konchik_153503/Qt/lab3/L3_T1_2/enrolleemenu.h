#ifndef ENROLLEEMENU_H
#define ENROLLEEMENU_H


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
#include "stupid_list.h"
#include "enrollee.h"

class EnrolleeMenu : public QDialog
{
    Q_OBJECT
protected:

    QLineEdit* lineName;
    QLineEdit* lineSurname;
    QLineEdit* linePatronymic;
    QLineEdit* lineCity;
    QSpinBox* score;



    QGridLayout* lay;
    QPushButton* Ok;
    QPushButton* Cancel;



public:

    EnrolleeMenu()
        : lineName(new QLineEdit), lineSurname(new QLineEdit),
          linePatronymic(new QLineEdit), lineCity(new QLineEdit), score(new QSpinBox),
          lay(new QGridLayout), Ok(new QPushButton), Cancel(new QPushButton)
    {
        setWindowFlags(Qt::Window | Qt::Tool);
        setModal(true);


        lay->addWidget(new QLabel("Фамилия: "), 0, 0);
        lay->addWidget(lineSurname, 0, 1);
        lineSurname->setMaxLength(100);
        lineSurname->setValidator(new QRegularExpressionValidator(QRegularExpression("^[^а-яА-ЯёЁ]+$"), this));

        lay->addWidget(new QLabel("Имя: "), 1, 0);
        lay->addWidget(lineName, 1, 1);
        lineName->setMaxLength(100);
        lineName->setValidator(new QRegularExpressionValidator(QRegularExpression("^[^а-яА-ЯёЁ]+$"), this));

        lay->addWidget(new QLabel("Отчество: "), 2, 0);
        lay->addWidget(linePatronymic, 2, 1);
        linePatronymic->setMaxLength(100);
        linePatronymic->setValidator(new QRegularExpressionValidator(QRegularExpression("^[^а-яА-ЯёЁ]+$"), this));

        lay->addWidget(new QLabel("Город: "), 3, 0);
        lay->addWidget(lineCity, 3, 1);
        lineCity->setMaxLength(100);
        lineCity->setValidator(new QRegularExpressionValidator(QRegularExpression("^[^а-яА-ЯёЁ]+$"), this));


        lay->addWidget(new QLabel("Баллы: "), 4, 0);
        lay->addWidget(score, 4, 1);
        score->setRange(0, 400);


        Ok = new QPushButton("&Ок");
        lay->addWidget(Ok, 5, 0);

        Cancel = new QPushButton("&Отмена");
        lay->addWidget(Cancel, 5, 1);

        setLayout(lay);
    }

    QString getName() { return lineName->text(); }
    QString getSurname() { return lineSurname->text(); }
    QString getPatronymic() { return linePatronymic->text(); }
    QString getCity() { return lineCity->text(); }
    int getScore() { return score->value(); }

};

class EnrolleeMenuAdd : public EnrolleeMenu
{
    Q_OBJECT

public:
    EnrolleeMenuAdd() {

        setWindowTitle("Добавить");

        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
    }

    void activate() {

        lineName->setText("");
        lineSurname->setText("");
        linePatronymic->setText("");
        lineCity->setText("");
        score->setValue(0);

        show();
        activateWindow();
    }
};


class EnrolleeMenuEdit : public EnrolleeMenu
{
    Q_OBJECT

public:
    EnrolleeMenuEdit() {
        setWindowTitle("Редактировать");

        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
    }

    void activate(stupid_list::list<Enrollee>::iterator it) {

        lineName->setText((*it).getName());
        lineSurname->setText((*it).getSurname());
        linePatronymic->setText((*it).getPatronymic());
        lineCity->setText((*it).getCity());
        score->setValue((*it).getScore());

        show();
        activateWindow();
    }

};

//class EnrolleeMenuView : public EnrolleeMenu
//{
//    Q_OBJECT

//public:
//    EnrolleeMenuView() {
//        setWindowTitle("Информация");

//        lineName->setReadOnly(true);
//        lineSurname->setReadOnly(true);
//        linePatronymic->setReadOnly(true);
//        lineCity->setReadOnly(true);
//        score->setReadOnly(true);
//        score->setButtonSymbols(QAbstractSpinBox::NoButtons);

//        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
//        connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
//    }

//    void activate(stupid_list::list<Enrollee>::iterator it) {

//        lineName->setText((*it).getName());
//        lineSurname->setText((*it).getSurname());
//        linePatronymic->setText((*it).getPatronymic());
//        lineCity->setText((*it).getCity());
//        score->setValue((*it).getScore());

//        show();
//        activateWindow();
//    }
//};

#endif // ENROLLEEMENU_H
