#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class Box : public QSpinBox {
    Q_OBJECT
public:
    QSpinBox* spb;
    Box(QWidget* parent);
};

class Button : public QPushButton {
    Q_OBJECT

public:
    QPushButton* btn;
    Button(QWidget* parent);

};

class Screen : public QLCDNumber {
    Q_OBJECT
private:
    int currentVal;
    QLCDNumber* screen;
public:

    Screen(QWidget* parent);

public slots:
    void set(int);
};


class Elevator;


class Scene : public QWidget {
    Q_OBJECT

private:
    QTimer* moveTimer;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QBrush* background;
    Elevator* rocket;
    QWidget* w;
    Box* box;
    Button* button;
    Screen* screen;
    int current_floor;
    int new_floor;
    int startY;
    int endY;

    bool flag;
    bool up; // вверх

public:
    friend Elevator;
    Scene(QWidget* parent = nullptr);

public slots:
    void checkElevCoords();
    void toFloor(int);
    void movingProcess();
    void moveByY();
    void isFloorReached();

signals:
    void stopMoving();
    void floorReached();
    void floorNotReached();
};


class Elevator : public QGraphicsRectItem {
private:
    QBrush* rocketPicture;
    int yspeed;

public:
    Elevator(int sceneWidth, int sceneHeight);
    friend Scene;
    virtual void advance(int phase) override;
};



#endif // MAINWINDOW_H
