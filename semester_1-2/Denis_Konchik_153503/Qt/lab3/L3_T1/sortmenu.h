#ifndef SORTMENU_H
#define SORTMENU_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class SortMenu : public QDialog
{
    Q_OBJECT
protected:

    QPushButton* Ok;
    QPushButton* Cancel;

    QComboBox* order;
    QComboBox* field;

public:

    SortMenu()
        : Ok(new QPushButton("&Ок")), Cancel(new QPushButton("&Отмена")),
          order(new QComboBox), field(new QComboBox)
    {
        setWindowFlags(Qt::Window | Qt::Tool);
        setWindowTitle("Сортировка");
        setModal(true);

        order->addItems(QStringList() << "Возрастание" << "Убывание");
        field->addItems(QStringList() << "Наименование" << "Количество" << "Цена" << "Дата");

        QVBoxLayout* comboLay = new QVBoxLayout;
        comboLay->addWidget(order);
        comboLay->addWidget(new QLabel);
        comboLay->addWidget(field);

        QHBoxLayout* buttonsLay = new QHBoxLayout;
        buttonsLay->addWidget(Ok);
        buttonsLay->addWidget(Cancel);

        QVBoxLayout* mainLay = new QVBoxLayout;
        mainLay->addItem(comboLay);
        mainLay->addItem(buttonsLay);

        setLayout(mainLay);

        connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
        connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
    }

    void activate() {
        order->setCurrentIndex(0);
        field->setCurrentIndex(0);

        show();
        activateWindow();

    }

    int getOrder() {
        return order->currentIndex();
    }

    int getField() {
        return field->currentIndex();
    }
};

#endif // SORTMENU_H
