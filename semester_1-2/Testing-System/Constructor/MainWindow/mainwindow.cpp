#include "mainwindow.h"
#include "ui_mainwindow.h"

StatusBar* Test::statusBar = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , test(nullptr)
    , taskChoose(new TaskChoose)
{
    ui->setupUi(this);

    setWindowTitle("Test Constructor");

    slot_testRemoved();


    Test::statusBar = ui->statusBar;

    // Соединение кнопок добавления и удаления заданий
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
  //  connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::checkTasksLimit);
    connect(ui->removeTaskButton, &QPushButton::clicked, this, &MainWindow::removeTask);
  //  connect(ui->removeTaskButton, &QPushButton::clicked, this, &MainWindow::checkTasksLimit);

    // Соединение menuBar
    connect(ui->CreateTest, &QAction::triggered, this, &MainWindow::createTest);
    connect(ui->OpenTest, &QAction::triggered, this, &MainWindow::openTest);
    connect(ui->RemoveTest, &QAction::triggered, this, &MainWindow::removeTest);
    connect(ui->SaveTest, &QAction::triggered, this, &MainWindow::saveTest);
    connect(ui->SaveAsTest, &QAction::triggered, this, &MainWindow::saveAsTest);
    connect(ui->exportPDF, &QAction::triggered, this, &MainWindow::exportPDF);

    // Соединение taskListView
    connect(ui->taskListView, &QListWidget::clicked, this, &MainWindow::taskListView_clicked);
    connect(ui->taskListView->model(), &QAbstractItemModel::rowsMoved, this, &MainWindow::taskListView_rowsMoved);
    connect(ui->taskListView, &TaskListView::taskPasted, this, &MainWindow::on_taskPasted);
    connect(ui->taskListView, &TaskListView::taskCopied, this, &MainWindow::on_taskCopied);

    // Соединение time
    connect(ui->timeCheckBox, &QCheckBox::clicked, this, &MainWindow::timeCheckBox_clicked);
    connect(ui->timeSpinBox, &QSpinBox::valueChanged, this, &MainWindow::timeSpinBox_valueChanged);

}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::timeCheckBox_clicked(bool checked)
{
    ui->timeSpinBox->setEnabled(checked);

    test->setPassingTime(checked, ui->timeSpinBox->value());
}

void MainWindow::timeSpinBox_valueChanged(int arg1)
{
    if (test)
        test->setPassingTime(ui->timeCheckBox->isChecked(), arg1);
}

int MainWindow::checkUnsavedChanges() {


    if (test && test->hasUnsavedChanges()) {

        int ret = QMessageBox::warning(this, windowTitle(),
                                       QString("The test \"") + test->getUrl().fileName() + QString("\" has been modified.\nDo you want to save your changes?"),
                                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
                                       );

        if (ret == QMessageBox::Save)
            test->save();

        return ret;
    }

    return 0;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (checkUnsavedChanges() == QMessageBox::Cancel)
        event->ignore();
}




