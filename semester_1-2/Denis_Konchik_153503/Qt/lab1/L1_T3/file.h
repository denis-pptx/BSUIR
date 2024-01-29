#ifndef FILE_H
#define FILE_H

#include "date.h"
#include <fstream>
#include <QFile>
#include <regex>
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QTimer>
using namespace std;

extern int N;
extern Date* dateArray;
extern QString storage;
extern bool CloseFile;


class File : public QObject {
    Q_OBJECT
public:
    void parseFile();
    void insertInFile(int, QString, bool = false);
    void msgFileBadDate(QString badDate, int strNum);
signals:
    void closeMainWindow();
};



#endif // FILE_H
