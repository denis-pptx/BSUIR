#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets>
#include <QLayout>

#include "allbuttons.h"
#include "circle.h"
#include "triangle.h"
#include "Ngon.h"
#include "star.h"
#include "drawing.h"
#include "tetragon.h"

class MainWidget : public QWidget {
    Q_OBJECT

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QHBoxLayout* hLay;
    QVBoxLayout* vLay;
    allButtons* buttons;

public:
    MainWidget(QWidget *parent = nullptr);

    void configureSceneAndView();
    void configureLayouts();
    void connectButtons();

public slots:
    void createRectangle();
    void createSquare();
    void createCircle();
    void createTriangle();
    void createRhomb();
    void createHexagon();
    void createStar();
    void drawFigure();
    void showInfo();




};
#endif // MAINWIDGET_H
