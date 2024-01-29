#include "mainwindow.h"
#include "ui_mainwindow.h"

Scene::Scene(QWidget* parent)
    : QWidget(parent), current_floor(1), new_floor(1), flag(true)
{


    // Основная сцена

    w = new QWidget();
    w->setWindowTitle("Это лифт");

    scene = new QGraphicsScene(0, 0, 1280, 720);
    view = new QGraphicsView(scene, w);
    view->setGeometry(0, 0, 1550 , 805);

    scene->setBackgroundBrush(QBrush(QImage(":/image/space.jpg")));

    rocket = new Elevator(scene->width(), scene->height());
    scene->addItem(rocket);
    box = new Box(w);
    button = new Button(w);
    screen = new Screen(w);

    view->show();
    w->showMaximized();

    QObject::connect(box->spb, SIGNAL(valueChanged(int)), this, SLOT(toFloor(int)));
    QObject::connect(button->btn, SIGNAL(clicked()), this, SLOT(movingProcess()));
    QObject::connect(this, SIGNAL(floorNotReached()), this, SLOT(moveByY()));

}

void Scene::movingProcess() {
    // Процесс движения

    if (new_floor == current_floor) {
        return;
    }

    // Направление
    rocket->yspeed = new_floor > current_floor ? -1 : 1;
    up = new_floor > current_floor ? true : false;

    emit floorNotReached();
}

void Scene::moveByY()  {
    // Передвижение лифта по оси Y

    box->spb->setReadOnly(true);
    QObject::disconnect(box->spb, SIGNAL(valueChanged(int)), this, SLOT(toFloor(int)));
    QObject::disconnect(button->btn, SIGNAL(clicked()), this, SLOT(movingProcess()));

    // Выбор стартовой точки
    if (up && flag) {
        startY = 40; endY = -770;
    } else if (up && !flag) {
        screen->set(++current_floor);
        startY = 100; endY = 40;
    } else if (!up && flag) {
        startY = 40; endY = 500;
    } else if (!up && !flag) {
        screen->set(--current_floor);
        startY = -770; endY = 40;
    }


    rocket->setPos(100, startY);

    moveTimer = new QTimer;
    QObject::connect(moveTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    QObject::connect(moveTimer, SIGNAL(timeout()), this, SLOT(checkElevCoords()));
    QObject::connect(this, SIGNAL(stopMoving()), moveTimer, SLOT(stop()));
    QObject::connect(this, SIGNAL(floorReached()), moveTimer, SLOT(stop()));
    moveTimer->start(1000 / 500);
}


void Scene::checkElevCoords() {
    // Проверка координат лифта

    if (up) {
        if (rocket->y() < endY) {
            emit stopMoving();
            flag = !flag;
            isFloorReached();
        }
    } else {
        if (rocket->y() > endY) {
            emit stopMoving();
            flag = !flag;
            isFloorReached();
        }
    }

}



void Scene::isFloorReached() {
    // Достигнут ли этаж

    if (new_floor == current_floor) {
        emit floorReached();

        box->spb->setReadOnly(false);
        QObject::connect(box->spb, SIGNAL(valueChanged(int)), this, SLOT(toFloor(int)));
        QObject::connect(button->btn, SIGNAL(clicked()), this, SLOT(movingProcess()));
    }
    else
        emit floorNotReached();

}

void Scene::toFloor(int val) {
    new_floor = val;
}

Elevator::Elevator(int sceneWidth, int sceneHeight)
    : QGraphicsRectItem(0)
{
    // Конструктор создания лифта

    rocketPicture = new QBrush(QImage(":/image/rocket.png").scaled(sceneWidth / 2, sceneHeight / 2, Qt::KeepAspectRatio));

    setRect(370 * 1.1, 370, (sceneWidth / 3) * 0.6, sceneHeight / 2);
    // setPen(Qt::NoPen);
    setPen(QPen(Qt::black, 1, Qt::DashDotLine));

    setBrush(*rocketPicture);
    setPos(100, 40);
}

void Elevator::advance(int phase) {
    // Сдвиг лифта
    moveBy(0, yspeed);
}




Box::Box(QWidget* parent) {
    // Конструктор создания панели выбора этажа

    spb = new QSpinBox(parent);

    spb->setRange(1,10);
    spb->setSuffix(" floor");
    spb->setWrapping(true);
    spb->setButtonSymbols(QSpinBox::UpDownArrows);
    spb->setGeometry(15,15,100,30);

    spb->show();
}

Button::Button(QWidget* parent) {
    // Конструктор создания кнопки GO

    btn = new QPushButton(parent);

    btn->setText("GO");
    btn->setGeometry(14,59,101,30);

    btn->show();
}

Screen::Screen(QWidget* parent) : currentVal(1) {
    // Конструктор создания экрана этажей

    screen = new QLCDNumber(2, parent);

    screen->display(1);
    screen->setFixedHeight(50);
    screen->setGeometry(15, 105, 100, 100);

    screen->show();
}


void Screen::set(int val) {
    // Установка значения на экране этажей

    currentVal = val;
    screen->display(currentVal);
}


