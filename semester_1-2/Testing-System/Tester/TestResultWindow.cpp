#include "TestResultWindow.h"
#include "ui_TestResultWindow.h"

TestResultWindow::TestResultWindow(TestResult testResult, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestResultWindow)
{
    ui->setupUi(this);

    setWindowTitle("Тест завершен");
    resize(260, 140);

    ui->surname_lineEdit->setText(testResult.name.first);
    ui->name_lineEdit->setText(testResult.name.second);
    ui->time_lineEdit->setText(testResult.time);

    if (testResult.testExecute.tasks.second == 0) {
        ui->taskNumber_lineEdit->setText("0 / 0 (100%)");
        ui->watchMistakesButton->setEnabled(false);
    } else {
        int right = testResult.testExecute.tasks.first;
        int total = testResult.testExecute.tasks.second;
        int percent = (double)right / total * 100;
        ui->taskNumber_lineEdit->setText(
                    QString::number(right) + " / " + QString::number(total) + " (" + QString::number(percent) + "%)");
    }

    if (testResult.testExecute.score.second == 0) {
        ui->score_lineEdit->setText("0 / 0 (100%)");
    } else {
        int right = testResult.testExecute.score.first;
        int total = testResult.testExecute.score.second;
        int percent = (double)right / total * 100;
        ui->score_lineEdit->setText(
                    QString::number(right) + " / " + QString::number(total) + " (" + QString::number(percent) + "%)");
    }
}

TestResultWindow::~TestResultWindow()
{
    delete ui;
}

void TestResultWindow::on_goToMainWindowButton_clicked()
{
    close();
    emit goToMainWindow();
}

void TestResultWindow::on_watchMistakesButton_clicked()
{
    close();
    emit showMistakes();
}

