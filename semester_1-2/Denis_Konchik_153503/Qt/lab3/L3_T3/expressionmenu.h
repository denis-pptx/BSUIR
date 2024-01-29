#ifndef EXPRESSIONMENU_H
#define EXPRESSIONMENU_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

class ExpressionMenu : public QDialog
{
    Q_OBJECT
protected:

    QLineEdit* infix;
    QDoubleSpinBox* spinBox;

    QGridLayout* lay;
    QPushButton* Ok;
    QPushButton* Cancel;

public:

    ExpressionMenu()
        : infix(new QLineEdit), spinBox(new QDoubleSpinBox[5]),
          lay(new QGridLayout), Ok(new QPushButton), Cancel(new QPushButton)
    {
        setWindowFlags(Qt::Window | Qt::Tool);
        setModal(true);

        for (int i = 0; i < 5; i++)
            spinBox[i].setRange(-1000000, 1000000);

        lay->addWidget(new QLabel("Выражение: "), 0, 0);
        lay->addWidget(infix, 0, 1);
        infix->setMaxLength(100);

        QString nameNumbers[5] = {"a: ", "b: ", "c: ", "d: ", "e: "};
        for (int i = 0; i < 5; i++) {
            spinBox[i].setButtonSymbols(QAbstractSpinBox::NoButtons);
            lay->addWidget(new QLabel(nameNumbers[i]), i + 1, 0);
            lay->addWidget(&spinBox[i], i + 1, 1);
        }

        Ok = new QPushButton("&Ок");
        lay->addWidget(Ok, 6, 0);

        Cancel = new QPushButton("&Отмена");
        lay->addWidget(Cancel, 6, 1);

        setLayout(lay);
    }



    QString getInfix() { return infix->text(); }

    double* getNumbers() {
        double* numbers = new double[5];

        for (int i = 0; i < 5; i++)
            numbers[i] = spinBox[i].value();

        return numbers;
    }


};

class ExpressionMenuAdd : public ExpressionMenu
{
    Q_OBJECT

public:
    ExpressionMenuAdd() {

        setWindowTitle("Добавить");

        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
    }

    void activate() {

        infix->setText("");
        for (int i = 0; i < 5; i++)
            spinBox[i].setValue(0);

        show();
        activateWindow();
    }
};
#endif // EXPRESSIONMENU_H
