#include "file.h"
#include "date.h"

regex rx("((0[1-9]|[12][0-9]|3[01])[- /.]"
             "(0[1-9]|1[012])[- /.]"
             "([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3}))");


void File::parseFile() {

    QFile file;
    file.setFileName(storage);

    if (file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        while (!stream.atEnd()) {
            QString line;
            stream >> line;


            if (line == "") {
                break;
            } else if (std::regex_match(line.toStdString().c_str(), rx) == 0) {
                msgFileBadDate(line, N + 1);
            }


            dateArray = (Date*)realloc(dateArray, ++N * sizeof(Date));
            dateArray[N - 1] = toDate(line);
        }
    } else {
        qDebug() << "BAD OPEN";
    }

    file.close();
}

void File::insertInFile(int n, QString date, bool addElement) {
    QFile file;
    file.setFileName(storage);


    if (file.open(QIODevice::ReadOnly | QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        stream.seek(12 * (n - 1));
        stream << date;
        if (addElement)
            stream << "\n";
    } else {
        qDebug() << "BAD OPEN";
    }

    file.close();
}

void File::msgFileBadDate(QString badDate, int strNum) {
    QDialog* Box = new QDialog;
    Box->setWindowTitle("Bad file");
    Box->setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* lay = new QVBoxLayout(Box);
    lay->addWidget(new QLabel("Некорректная дата: " + badDate +
                              "\nСтрока: " + QString::number(strNum)));


    Box->show();
    Box->activateWindow();
    emit closeMainWindow();
}
