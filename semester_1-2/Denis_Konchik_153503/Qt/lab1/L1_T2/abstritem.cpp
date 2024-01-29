#include "abstritem.h"

AbstrItem::AbstrItem(QString name)
{
    this->name = name;

    scl = 1;
    rotate = 0;

    name = "";
    P = 0;
    S = 0;
    C = QPoint(0, 0);

    sclRtD = new ScaleRotationDialog;

    R = rand() % 256;
    G = rand() % 256;
    B = rand() % 256;

}


void AbstrItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

    if (event->button() & Qt::LeftButton) {
        delete this;
    } else if (event->button() & Qt::RightButton) {
        showFigureInfo();
    } else if (event->button() & Qt::MiddleButton) {
        sclRtD->show();
        sclRtD->activateWindow();
    }
    //update();
};

void AbstrItem::wheelEvent(QGraphicsSceneWheelEvent *event) {

    if (event->modifiers() == Qt::ControlModifier) {

        if (event->delta() > 0)
            rotate += 2;
        else if (event->delta() < 0)
            rotate -= 2;

        setTransformOriginPoint(sclRtD->point);
        setRotation(rotate);

    } else {

        double sclRatio = 1.02;

        if (event->delta() > 0 && scl <= 3) {
            scl *= sclRatio;
            P *= sclRatio;
            S *= sclRatio * sclRatio;
            C *= sclRatio;
        }
        else if (event->delta() < 0 && scl >= 1.0 / 3) {
            scl /= sclRatio;
            P /= sclRatio;
            S /= sclRatio * sclRatio;
            C /= sclRatio;
        }

        setTransformOriginPoint(sclRtD->point);
        setScale(scl);
    }
}


void AbstrItem::showFigureInfo() {
    QDialog* window = new QDialog;
    window->setWindowTitle(name);
    window->setWindowFlags(Qt::Window | Qt::Tool);

    int posH = 0;
    QGridLayout* statusLay = new QGridLayout;
    statusLay->addWidget(new QLabel("Периметр: "), posH++, 0);
    if (name != "Звезда") statusLay->addWidget(new QLabel("Площадь: "), posH++, 0);
    statusLay->addWidget(new QLabel("Центр масс: "), posH++, 0);

    posH = 0;
    statusLay->addWidget(new QLabel(QString::number(ceil(P))), posH++, 1);
    if (name != "Звезда") statusLay->addWidget(new QLabel(QString::number(ceil(S))), posH++, 1);
    statusLay->addWidget(new QLabel("(" + QString::number(C.x()) + ", " + QString::number(C.y()) + ")"), posH++, 1);

    QVBoxLayout* mainLay = new QVBoxLayout;
    mainLay->addItem(statusLay);

    if (name == "Треугольник")
        mainLay->addWidget(new QLabel("Центр масс относительно \n"
                                      "начального положения"));

    window->setLayout(mainLay);
    window->show();
    window->activateWindow();
}


ScaleRotationDialog::ScaleRotationDialog() {

    point = QPoint(0, 0);

    setWindowTitle("Настройки");
    setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* mainLay = new QVBoxLayout;
    QGridLayout* confLay = new QGridLayout;

    confLay->addWidget(new QLabel("Координата X: "), 0, 0);
    spbX = new QSpinBox;
    spbX->setRange(0, 900);
    spbX->setValue(point.x());
    confLay->addWidget(spbX, 0, 1);

    confLay->addWidget(new QLabel("Координата Y: "), 1, 0);
    spbY = new QSpinBox;
    spbY->setRange(0, 700);
    spbY->setValue(point.y());
    confLay->addWidget(spbY, 1, 1);

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отменить");

    confLay->addWidget(Ok, 2, 0);
    confLay->addWidget(Cancel, 2, 1);

    mainLay->addWidget(new QLabel("Поворот / масштаб \n"
                                  "относительно точки: "));
    mainLay->addItem(confLay);

    setLayout(mainLay);

    QObject::connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(Ok, &QPushButton::clicked, this, &ScaleRotationDialog::setScaleRotationPoint);
    QObject::connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void ScaleRotationDialog::setScaleRotationPoint() {
    point = QPoint(spbX->value(), spbY->value());
}
