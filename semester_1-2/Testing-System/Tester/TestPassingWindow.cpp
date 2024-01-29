#include "TestPassingWindow.h"
#include "ui_TestPassingWindow.h"

PassingTestWindow::PassingTestWindow(Test* test, QPair<QString,QString> name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassingTestWindow),
    testResultWindow(nullptr),
    test(test),
    timer(nullptr),
    currentTaskIndex(0),
    passedTime(0),
    name(name)
{
    ui->setupUi(this);

    setWindowTitle("Тест");

    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &PassingTestWindow::updateTime);
    timer->start(1000);

    if (test->getPassingTime().first)
        ui->timeLabel->setText(secondsToFormatStr(test->getPassingTime().second * 60));
    else
        ui->timeLabel->hide();


    if (test->size())
        (*test)[currentTaskIndex]->setTaskNum(currentTaskIndex + 1, test->size());

    ui->prevButton->setEnabled(false);

    if (test->size() > 1) {
        ui->taskViewWidget->setTask((*test)[currentTaskIndex]);
        ui->nextButton->setEnabled(true);
        ui->finishButton->setEnabled(false);
    } else if (test->size() == 1) {
        ui->taskViewWidget->setTask((*test)[currentTaskIndex]);
        ui->nextButton->setEnabled(false);
        ui->finishButton->setEnabled(true);
    } else { // test->size() = 0
        ui->taskViewWidget->setNoTasks();
        ui->nextButton->setEnabled(false);
        ui->finishButton->setEnabled(true);
    }
}

PassingTestWindow::~PassingTestWindow()
{
    delete ui;
}

void PassingTestWindow::on_goToMainWindowButton_clicked()
{
    QMessageBox messageBox(QMessageBox::Question,
                           "Tester", "Вы действительно хотите вернуться?\n"
                                     "Текущий тест будет закрыт.",
                           QMessageBox::Yes | QMessageBox::No, this);
    messageBox.setButtonText(QMessageBox::Yes, tr("Да"));
    messageBox.setButtonText(QMessageBox::No, tr("Нет"));

    if (messageBox.exec() == QMessageBox::Yes) {
        close();
        timer->stop();
        emit goToMainWindow();
    }
}


void PassingTestWindow::on_nextButton_clicked()
{
    ui->prevButton->setEnabled(true);

    currentTaskIndex++;
    (*test)[currentTaskIndex]->setTaskNum(currentTaskIndex + 1, test->size());

    if (currentTaskIndex == (test->size() - 1)) {
        ui->nextButton->setEnabled(false);
        ui->finishButton->setEnabled(true);
    }

    ui->taskViewWidget->setTask((*test)[currentTaskIndex]);
}


void PassingTestWindow::on_prevButton_clicked()
{
    ui->nextButton->setEnabled(true);

    currentTaskIndex--;
    (*test)[currentTaskIndex]->setTaskNum(currentTaskIndex + 1, test->size());

    if (currentTaskIndex == 0)
        ui->prevButton->setEnabled(false);

    ui->taskViewWidget->setTask((*test)[currentTaskIndex]);
}


void PassingTestWindow::on_finishButton_clicked()
{

    timer->stop();

    testResultWindow = new TestResultWindow(TestResult{name, test->execute(), secondsToFormatStr(passedTime)});
    connect(testResultWindow, &TestResultWindow::goToMainWindow, this, &PassingTestWindow::goToMainWindow);
    connect(testResultWindow, &TestResultWindow::showMistakes, this, &PassingTestWindow::on_showMistakes);
    hide();
    testResultWindow->show();


}

void PassingTestWindow::updateTime()
{
    passedTime++;

    if (test->getPassingTime().first) {
        ui->timeLabel->setText(secondsToFormatStr(test->getPassingTime().second * 60 - passedTime));
    }

    if (test->getPassingTime().first && passedTime == test->getPassingTime().second * 60) {
        timer->stop();
        on_finishButton_clicked();
    }

}

QString PassingTestWindow::secondsToFormatStr(int seconds)
{
    int hours = seconds / 3600;
    int min = (seconds - hours * 3600) / 60;
    int sec = seconds - hours * 3600 - min * 60;

    QString str_hours = QString::number(hours);
    QString str_min = QString::number(min);
    QString str_sec = QString::number(sec);

    if (hours < 10) str_hours= "0" + str_hours;
    if (min < 10) str_min = "0" + str_min;
    if (sec < 10) str_sec = "0" + str_sec;

    QString str_time = str_hours + ":" + str_min + ":" + str_sec;
    return str_time;
}

void PassingTestWindow::on_showMistakes()
{
    ui->timeLabel->hide();


    currentTaskIndex = 0;
    (*test)[currentTaskIndex]->setTaskNum(currentTaskIndex + 1, test->size());

    ui->prevButton->setEnabled(false);
    ui->finishButton->setEnabled(true);
    ui->finishButton->setText("Результат");

    if (test->size() > 1) {
        ui->taskViewWidget->setTask((*test)[currentTaskIndex]);
        ui->nextButton->setEnabled(true);
    } else if (test->size() == 1) {
        ui->taskViewWidget->setTask((*test)[currentTaskIndex]);
        ui->nextButton->setEnabled(false);
    }

    test->setWatchMistakesEnabled(true);

    show();
}
