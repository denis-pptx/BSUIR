#ifndef ABSTRITEM_H
#define ABSTRITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>

#include <algorithm>
using std::min, std::max;

#define PI 3.1415926535

class ScaleRotationDialog : public QDialog {

public:
    ScaleRotationDialog();

    QSpinBox* spbX;
    QSpinBox* spbY;
    QPoint point;

public slots:
    void setScaleRotationPoint();
};


class AbstrItem : public QGraphicsItem, public QObject {

public:
    AbstrItem(QString name = "null");

protected slots:
    void scaleFunc();
    void rotatioFunc();

protected:

    double scl;
    double rotate;

    QString name;
    double P;
    double S;
    QPoint C;

    ScaleRotationDialog* sclRtD;

    int R;
    int G;
    int B;

    void showFigureInfo();

    virtual void calculateInfo() = 0;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;

};


#endif // ABSTRITEM_H
