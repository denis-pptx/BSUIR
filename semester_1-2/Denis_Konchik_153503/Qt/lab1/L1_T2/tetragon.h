#ifndef TETRAGON_H
#define TETRAGON_H

#include "abstritem.h"
class Tetragon : public AbstrItem
{

protected:

    QPoint p[4];
    double alpha;

    int weight;
    int height;

    void calculateInfo() override;
public:
    Tetragon(QString name, double alpha);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

class InputDialogTetragon : public QDialog {
    Q_OBJECT
protected:
    QSpinBox* spbW;
    QSpinBox* spbH;

public:
    InputDialogTetragon(QString name);
    int getW();
    int getH();
};

class Square : public Tetragon
{
public:
    Square();
};

class Rectangle : public Tetragon
{
public:
    Rectangle();
};

class Rhomb : public Tetragon
{
public:
    Rhomb();
};
#endif // TETRAGON_H
