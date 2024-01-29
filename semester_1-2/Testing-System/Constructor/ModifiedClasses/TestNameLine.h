#ifndef TESTNAMELINE_H
#define TESTNAMELINE_H

#include <QLineEdit>
#include <QEvent>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QString>
#include <QFileInfo>

// ЛИНИЯ С ИМЕНЕМ ТЕСТА
class TestNameLine : public QLineEdit
{
private:
    QUrl fileUrl; // Путь к файлу

public slots:
    // Добавление и удаление "*" возле имени
    void addStar() { setText(fileUrl.fileName() + "*"); }
    void removeStar() { setText(fileUrl.fileName()); }

public:
    TestNameLine(QWidget* parent = nullptr) : QLineEdit(parent) {
        setFileUrl(QUrl(""));
    }

    // Двойной клик по линии
    virtual void mouseDoubleClickEvent(QMouseEvent*) {

        if (fileUrl.toString() != "") {
            QString strDirectoryUrl = fileUrl.toString();
            strDirectoryUrl.resize(strDirectoryUrl.length() - fileUrl.fileName().length());


            QDesktopServices::openUrl(QUrl(strDirectoryUrl));
        }

    }

    // Установить Url
    void setFileUrl(QUrl fileUrl) {

        this->fileUrl = fileUrl;

        if (fileUrl.toString() == "") {
            setText("NO ACTIVE TEST");
            setEnabled(false);
        }
        else {
            setText(fileUrl.fileName());
            setEnabled(true);
        }
    }
};



#endif // TESTNAMELINE_H
