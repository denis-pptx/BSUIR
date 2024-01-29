#include "TaskView.h"
#include "ui_TaskView.h"

TaskView::TaskView(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TaskView)
    , optionsLayout(new QGridLayout)
    , optionsWidget(new QWidget)
    , currentAnswers(Answers::USER)
{
    ui->setupUi(this);

    ui->switchAnswersButton->hide();
    ui->taskResultLabel->hide();
    ui->whoseAnswersLabel->hide();

}

TaskView::~TaskView()
{
    delete ui;
}





