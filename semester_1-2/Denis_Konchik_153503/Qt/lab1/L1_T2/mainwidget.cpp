#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Фигуры");

    configureSceneAndView();
    configureLayouts();
    connectButtons();

}

void MainWidget::configureSceneAndView() {
    setFixedSize(900, 700);

    scene = new QGraphicsScene(150, 100, 800, 600, this);
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->show();
}

void MainWidget::configureLayouts() {
    buttons = new allButtons(this);
    hLay = new QHBoxLayout;
    vLay = new QVBoxLayout;

    hLay->addWidget(buttons->rectangleButton);
    hLay->addWidget(buttons->squareButton);
    hLay->addWidget(buttons->rhombButton);
    hLay->addWidget(buttons->circleButton);
    hLay->addWidget(buttons->triangleButton);
    hLay->addWidget(buttons->hexagonButton);
    hLay->addWidget(buttons->starButton);
    hLay->addWidget(buttons->drawButton);
    hLay->addWidget(buttons->infoButton);

    vLay->addWidget(view);
    vLay->addLayout(hLay);

    setLayout(vLay);
}

void MainWidget::connectButtons() {
    connect(buttons->rectangleButton, SIGNAL(clicked()), this, SLOT(createRectangle()));
    connect(buttons->squareButton, SIGNAL(clicked()), this, SLOT(createSquare()));
    connect(buttons->circleButton, SIGNAL(clicked()), this, SLOT(createCircle()));
    connect(buttons->triangleButton, SIGNAL(clicked()), this, SLOT(createTriangle()));
    connect(buttons->rhombButton, SIGNAL(clicked()), this, SLOT(createRhomb()));
    connect(buttons->hexagonButton, SIGNAL(clicked()), this, SLOT(createHexagon()));
    connect(buttons->starButton, SIGNAL(clicked()), this, SLOT(createStar()));
    connect(buttons->drawButton, SIGNAL(clicked()), this, SLOT(drawFigure()));
    connect(buttons->infoButton, SIGNAL(clicked()), this, SLOT(showInfo()));
}

void MainWidget::createRectangle() {

    scene->addItem(new class Rectangle());
}

void MainWidget::createSquare() {
    scene->addItem(new class Square());
}
void MainWidget::createCircle() {
    scene->addItem(new class Circle());
}

void MainWidget::createTriangle() {
    scene->addItem(new class Triangle());
}

void MainWidget::createRhomb() {
    scene->addItem(new class Rhomb());
}

void MainWidget::createHexagon() {
    scene->addItem(new class Ngon());
}

void MainWidget::createStar() {
    scene->addItem(new class Star());
}

void MainWidget::drawFigure() {

    QWidget* drawingWindow = new QWidget();
    drawingWindow->setWindowFlags(Qt::Tool);
    drawingWindow->setWindowTitle("Рисование");
    drawingWindow->setFixedSize(800, 600);

    Drawing* paint = new Drawing(drawingWindow);
    paint->setFixedSize(800, 600);
    drawingWindow->show();
    drawingWindow->activateWindow();
}

void MainWidget::showInfo() {
    QLabel* infoWindow = new QLabel(this);
    infoWindow->setWindowTitle("Info");
    infoWindow->setWindowFlags(Qt::Tool);

    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(new QLabel("Операции над фигурами: \n"
                              "ЛКМ - перемещать \n"
                              "2 * ЛКМ - удалить \n"
                              "2 * ПКМ - информация \n"
                              "2 * СКМ - настройка\n"
                              "Колесико - зум \n"
                              "Ctrl + колесико - поворот \n\n"
                              "Рисование на холсте: \n"
                              "КМ - поставить точку \n"
                              "2 * КМ - замкнуть контур"));


    infoWindow->setLayout(lay);


    infoWindow->show();
    infoWindow->activateWindow();
}


