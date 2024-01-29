#include "Test.h"


Test::Test(QUrl url_)
    : passingTime(QPair<bool, int>(false, 1))
    , url(url_)
{


}

QString Test::getFileName() {
    return url.fileName().section(".", 0, 0);
}

void Test::pasteTask(int numberOfPasted, int placeToPaste) {
    Task* copied = taskList[numberOfPasted]->getCopy();
    taskList.insert(taskList.begin() + placeToPaste, copied);

    connect(copied, &TaskView::taskEdited, this, [=]() {
        setStatus(TestStatus::EDITED);
    });

    setStatus(TestStatus::EDITED);
}


void Test::addTask(Task* task) {

    taskList.push_back(task);

    connect(task, &TaskView::taskEdited, this, [=]() {
        setStatus(TestStatus::EDITED);
    });

    statusBar->taskAdded(task->getType());
    setStatus(TestStatus::EDITED);
}

void Test::removeTask(int i) {

    if (i < 0 || i >= taskList.size())
        throw std::exception();

    statusBar->taskRemoved((*(taskList.cbegin() + i))->getName());
    setStatus(TestStatus::EDITED);

    taskList.erase(taskList.cbegin() + i);


}

void Test::create() {

    QFile* file = new QFile;
    file->setFileName(url.toString());

    if (file->open(QIODevice::Truncate | QIODevice::WriteOnly))
        file->close();
    else
        qDebug() << "BAD CREATE";

    delete file;

    setStatus(TestStatus::CREATED);
    statusBar->testCreated(url);
}

void Test::save() {

    QFile* file = new QFile;
    file->setFileName(url.toString());

    if (file->open(QIODevice::Truncate | QIODevice::WriteOnly)) {

        statusBar->testSaved(url);

        // Число заданий
        int32_t N = taskList.size();
        file->write((char*)&N, sizeof(int32_t));

        // Время прохождения
        file->write((char*)&(passingTime.first), sizeof(bool));
        file->write((char*)&(passingTime.second), sizeof(int32_t));

        // Запись каждого задания
        for (int i = 0; i < taskList.size(); i++)
            taskList[i]->write(file);

        file->close();

    }
    else {
        qDebug() << "BAD OPEN";
    }

    delete file;

    setStatus(TestStatus::SAVED);
}

void Test::savePDF(QUrl fileUrl) {

    QTextDocument document;
    QFont font("Monospace", 10);
    font.setLetterSpacing(QFont::PercentageSpacing, 110);
    font.setStyleHint(QFont::Monospace);
    document.setDefaultFont(font);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMargins(10, 10, 10, 10), QPageLayout::Millimeter);
    printer.setOutputFormat(QPrinter::PdfFormat);

    QSizeF paperSize;
    paperSize.setWidth(printer.width());
    paperSize.setHeight(printer.height());
    document.setPageSize(paperSize);


    printer.setOutputFileName(fileUrl.toString());
    document.setPlainText("Фамилия: ______________\nИмя:     ______________\nВремя:   " +
                          (passingTime.first ? QString::number(passingTime.second) + " мин" : "∞") + "\n\n"
                          + toString(false));
    document.print(&printer);

    printer.setOutputFileName(fileUrl.toString().replace(getFileName(),
                                                         getFileName() + " (answers)"));
    document.setPlainText("Заданий: " + QString::number(size()) +
                          "\nБаллов:  " + QString::number(sumOfPrices()) + "\nВремя:   " +
                          (passingTime.first ? QString::number(passingTime.second) + " мин" : "∞") + "\n\n"
                          + toString(true));
    document.print(&printer);

    statusBar->testSavedPDF(fileUrl);
}

QString Test::toString(bool solved) {

    QString string = "";

    for (int i = 0; i < taskList.size(); i++)
        string = string + QString::number(i + 1) + ". " + taskList[i]->toString(solved) + "\n\n";

    return string;

}

void Test::saveAs(QUrl newUrl) {
    url = newUrl;
    save();
}

void Test::open() {

    QFile* file = new QFile;
    file->setFileName(url.toString());

    if (file->open(QIODevice::ReadOnly)) {

        statusBar->testOpened(url);

        // Число заданий
        int32_t N = 0;
        file->read((char*)&N, sizeof(int32_t));

        // Время прохождения
        file->read((char*)&(passingTime.first), sizeof(bool));
        file->read((char*)&(passingTime.second), sizeof(int32_t));

        for (int32_t i = 0; i < N; i++) {

            TaskType taskType;
            file->read((char*)&taskType, sizeof(int32_t));

            addTask(TaskService::objByType(taskType));

            taskList.back()->read(file);

        }

    }
    else
    {
        qDebug() << "BAD OPEN";
    }

    file->close();

    delete file;

    setStatus(TestStatus::OPENED);
    statusBar->testOpened(url);
}

void Test::remove() {
    QFile* file = new QFile;
    file->setFileName(url.toString());
    file->remove();
    file->close();
    delete file;

    setStatus(TestStatus::REMOVED);
    statusBar->testRemoved(url);
}

void Test::moveTask(int from, int to) {


    Task* moving = taskList[from];

    if (from < to)
        for (int i = from; i < to; i++)
            taskList[i] = taskList[i + 1];
    else
        for (int i = from; i > to; i--)
            taskList[i] = taskList[i - 1];

    taskList[to] = moving;

    setStatus(TestStatus::EDITED);
}

Task* Test::back() {
    return taskList.back();
}

Task* Test::operator[](int i) {
    return taskList[i];
}

void Test::setPassingTime(bool flag, int duration) {

    if (this->passingTime.second == duration
            && this->passingTime.first == flag)
        return;

    passingTime.first = flag;
    passingTime.second = duration;

    setStatus(TestStatus::EDITED);
}

void Test::setPassingTime(QPair<bool, int32_t> passingTime) {

    if (this->passingTime.second == passingTime.second
            && this->passingTime.first == passingTime.first)
        return;

    this->passingTime = passingTime;

    setStatus(TestStatus::EDITED);
}

QPair<bool, int32_t> Test::getPassingTime() {
    return passingTime;
}

int Test::size() {
    return taskList.size();
}

void Test::setStatus(TestStatus status) {
    this->status = status;

    if (status == TestStatus::EDITED)
        emit testEdited();
    else if (status == TestStatus::SAVED)
        emit testSaved();
    else if (status == TestStatus::CREATED)
        emit testCreated();
    else if (status == TestStatus::OPENED)
        emit testOpened();
    else if (status == TestStatus::REMOVED)
        emit testRemoved();

}

bool Test::hasUnsavedChanges() {
    return status == TestStatus::EDITED;
}

QUrl Test::getUrl() {
    return url;
}

int Test::sumOfPrices() {

    int sum = 0;

    for (int i = 0; i < taskList.size(); i++)
        sum += taskList[i]->getPrice();

    return sum;

}









