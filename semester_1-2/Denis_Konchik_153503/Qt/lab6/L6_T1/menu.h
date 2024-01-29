#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

enum MenuSettings {
    ADD,
    DELETE,
    FIND,
    SHOW
};

class Menu : public QDialog
{
    Q_OBJECT
protected:

    QLineEdit* textEdit;
    QSpinBox* numberEdit;


    QGridLayout* layout;
    QPushButton* Ok;
    QPushButton* Cancel;

    QLabel* lbl2;

public:

    Menu()
        : textEdit(new QLineEdit), numberEdit(new QSpinBox), layout(new QGridLayout),
          Ok(new QPushButton("&Ок")), Cancel(new QPushButton("&Отмена")), lbl2(new QLabel("Текст:"))
    {
        setWindowFlags(Qt::Window | Qt::Tool);
        setModal(true);

        setWindowTitle("Добавить");

        layout->addWidget(new QLabel("Ключ: "), 0, 0);
        layout->addWidget(numberEdit, 0, 1);
        numberEdit->setRange(-1000000000, 1000000000);

        layout->addWidget(lbl2, 1, 0);
        layout->addWidget(textEdit, 1, 1);
        textEdit->setMaxLength(20);


        layout->addWidget(Ok, 2, 0);
        layout->addWidget(Cancel, 2, 1);

        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));

        setLayout(layout);

        setFixedSize(layout->sizeHint());
    }

    void activate(MenuSettings setings) {

        switch (setings) {
        case ADD:
            textEdit->show();
            lbl2->show();
            setWindowTitle("Добавить");
            break;
        case DELETE:
            textEdit->hide();
            lbl2->hide();
            setWindowTitle("Удалить");
            break;
        case FIND:
            textEdit->hide();
            lbl2->hide();
            setWindowTitle("Поиск");
            break;
        case SHOW:
            textEdit->show();
            lbl2->show();
            setWindowTitle("Поиск");
            textEdit->setReadOnly(true);
            numberEdit->setReadOnly(true);
            numberEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
            break;
        default:
            throw _exception();
        }

        if (setings != MenuSettings::SHOW) {
            textEdit->setText("");
            numberEdit->setValue(0);
            textEdit->setReadOnly(false);
            numberEdit->setReadOnly(false);
            numberEdit->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        }


        setFixedSize(layout->sizeHint());

        show();
        activateWindow();
    }

    QString getText() { return textEdit->text(); }
    int getKey() { return numberEdit->value(); }

    void setText(QString text) { textEdit->setText(text); }
    void setKey(int key) { numberEdit->setValue(key); }

};
#endif // MENU_H
