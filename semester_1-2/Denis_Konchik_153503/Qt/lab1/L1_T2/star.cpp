#include "star.h"

Star::Star()
{

    InputDialogStar* dialog = new InputDialogStar;
    dialog->show();
    dialog->activateWindow();

    if (dialog->exec() == QDialog::Accepted) {

        peaksAmount = dialog->getPeaks();
        point = new QPoint[2 * peaksAmount];

        R = dialog->getR();

        calculateInfo();
    }
    delete dialog;

}

void Star::calculateInfo() {

    name = "Звезда";

    double alpha = PI / peaksAmount;
    QPoint Begining = QPoint(rand() % 600 + 200, rand() % 400 + 200);
    min_x = 2000; max_x = 0; min_y = 2000; max_y = 0;

    for (int i = 0; i < 2 * peaksAmount; i++) {
        if (i % 2) {
            point[i] = QPoint(R * cos(alpha * i), R * sin(alpha * i)) + Begining;

            min_x = min(min_x, point[i].x());
            max_x = max(max_x, point[i].x());

            min_y = min(min_y, point[i].y());
            max_y = max(max_y, point[i].y());

        } else {
            point[i] = QPoint(0.5 * R * cos(alpha * i), 0.5 * R * sin(alpha * i)) + Begining;
        }

    }

    int edge = sqrt(pow(point[0].x() - point[1].x(), 2) + pow(point[0].y() - point[1].y(), 2));
    P = 2 * edge * peaksAmount;
    C = QPoint((max_x - min_x) / 2, (max_y - min_y) / 2);
}


void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPolygon* plgn = new QPolygon;

    for (int i = 0; i < 2 * peaksAmount; i++)
        *plgn << point[i];

    painter->setBrush(QBrush(QColor(R, G, B)));
    painter->drawPolygon(*plgn);

    setFlags(QGraphicsItem::ItemIsMovable);
    Q_UNUSED(option); Q_UNUSED(widget);

}

QRectF Star::boundingRect() const {
    return QRectF(min_x, min_y, max_x - min_x, max_y - min_y);
}


InputDialogStar::InputDialogStar(QWidget* parent)
    : QDialog(parent, Qt::Window | Qt::Tool) {


    setWindowTitle("Звезда");
    setModal(true);

    QGridLayout* param = new QGridLayout;

    spbP = new QSpinBox;
    spbP->setRange(4, 50);
    spbP->setValue(4);
    param->addWidget(new QLabel("Вершин: "), 0, 0);
    param->addWidget(spbP, 0, 1);


    spbR = new QSpinBox;
    spbR->setRange(10, 300);
    spbR->setValue(100);
    param->addWidget(new QLabel("Радиус: "), 1, 0);
    param->addWidget(spbR, 1, 1);


    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отменить");
    param->addWidget(Ok, 2, 0);
    param->addWidget(Cancel, 2, 1);

    setLayout(param);

    connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

int InputDialogStar::getPeaks() {
    return spbP->value();
}

int InputDialogStar::getR() {
    return spbR->value();
}
