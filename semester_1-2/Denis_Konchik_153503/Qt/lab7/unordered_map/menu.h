#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDoubleSpinBox>

enum MenuSettings {
    ADD,
    ERASE,
    FIND,
    SHOW
};

class Menu : public QDialog
{
    Q_OBJECT
protected:

    QLineEdit* keyEdit;
    QLineEdit* valueEdit;



    QGridLayout* layout;
    QPushButton* Ok;
    QPushButton* Cancel;

    QLabel* lbl2;

public:

    Menu()
        : keyEdit(new QLineEdit), valueEdit(new QLineEdit), layout(new QGridLayout),
          Ok(new QPushButton("&Ok")), Cancel(new QPushButton("&Cancel")), lbl2(new QLabel("Value:"))
    {
        setWindowFlags(Qt::Window | Qt::Tool);
        setModal(true);

        setWindowTitle("Add");

        layout->addWidget(new QLabel("Key: "), 0, 0);
        layout->addWidget(keyEdit, 0, 1);
        keyEdit->setMaxLength(20);

        layout->addWidget(lbl2, 1, 0);
        layout->addWidget(valueEdit, 1, 1);
        valueEdit->setMaxLength(20);


        layout->addWidget(Ok, 2, 0);
        layout->addWidget(Cancel, 2, 1);

        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));

        setLayout(layout);

        setFixedSize(layout->sizeHint());
    }

    void activate(MenuSettings settings) {

        switch (settings) {
        case ADD:
            valueEdit->show();
            lbl2->show();
            setWindowTitle("insert");
            break;
        case ERASE:
            valueEdit->hide();
            lbl2->hide();
            setWindowTitle("erase");
            break;
        case FIND:
            valueEdit->hide();
            lbl2->hide();
            setWindowTitle("search");
            break;
        case SHOW:
            valueEdit->show();
            lbl2->show();
            setWindowTitle("search");
            valueEdit->setReadOnly(true);
            keyEdit->setReadOnly(true);
            break;
        default:
            throw _exception();
        }

        if (settings != MenuSettings::SHOW) {
            valueEdit->setText("");
            keyEdit->setText("");
            valueEdit->setReadOnly(false);
            keyEdit->setReadOnly(false);
        }


        setFixedSize(layout->sizeHint());

        show();
        activateWindow();
    }

    QString getKey() { return keyEdit->text(); }
    QString getValue() { return valueEdit->text(); }

    void setKey(QString key) { keyEdit->setText(key); }
    void setValue(QString text) { valueEdit->setText(text); }


};

#endif // MENU_H
