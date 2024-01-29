#ifndef ALLBUTTONS_H
#define ALLBUTTONS_H

#include <QPushButton>

class MainWidget;

class allButtons : public QWidget
{
    Q_OBJECT
private:
    QPushButton* rectangleButton;
    QPushButton* squareButton;
    QPushButton* circleButton;
    QPushButton* triangleButton;
    QPushButton* rhombButton;
    QPushButton* hexagonButton;
    QPushButton* parallelogramButton;
    QPushButton* starButton;
    QPushButton* drawButton;
    QPushButton* infoButton;

public:
    friend MainWidget;
    allButtons(QWidget* parent = nullptr);

signals:

};

#endif // ALLBUTTONS_H
