#ifndef NGON_H
#define NGON_H


#include "abstritem.h"

class Ngon : public AbstrItem
{

private:

    QPoint* p;
    int edge;
    int N;
    double R;

    int min_x, max_x, min_y, max_y;

    void calculateInfo() override;

public:
    Ngon();
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class InputDialogNgon : public QDialog {
    Q_OBJECT
private:
    QSpinBox* spbE;
    QSpinBox* spbN;

public:
    InputDialogNgon(QWidget* parent = nullptr);
    int getE();
    int getN();
};

#endif // NGON_H
