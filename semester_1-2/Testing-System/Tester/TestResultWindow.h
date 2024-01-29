#ifndef TESTRESULTWINDOW_H
#define TESTRESULTWINDOW_H

#include "TestResult.h"

#include <QWidget>
#include <QPair>
#include <QDialog>

namespace Ui {
class TestResultWindow;
}

class TestResultWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TestResultWindow(TestResult, QWidget *parent = nullptr);
    ~TestResultWindow();

public slots:
    void on_goToMainWindowButton_clicked();
    void on_watchMistakesButton_clicked();

signals:
    void goToMainWindow();
    void showMistakes();

private:
    Ui::TestResultWindow *ui;
};

#endif // TESTRESULTWINDOW_H
