QT       += core gui
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    MainWindow/TaskOperations/addTask.cpp \
    MainWindow/TaskOperations/removeTask.cpp \
    MainWindow/TaskOperations/checkLimit.cpp \
    MainWindow/taskListView.cpp \
    MainWindow/TestOperations/exportPDF.cpp \
    MainWindow/TestOperations/testSlots.cpp \
    MainWindow/TestOperations/create.cpp \
    MainWindow/TestOperations/open.cpp \
    MainWindow/TestOperations/save.cpp \
    MainWindow/TestOperations/remove.cpp \
    Task/TaskTypes/Entry.cpp \
    Task/TaskTypes/MultipleChoice.cpp \
    Task/TaskTypes/OrderIndication.cpp \
    Task/TaskTypes/SingleChoice.cpp \
    Task/TaskTypes/Task.cpp \
    Task/TaskTypes/TaskView.cpp \
    Task/TaskTypes/Comparison.cpp \
    Task/TaskChoose.cpp \
    Task/TaskViewWidget.cpp \
    Test.cpp \
    main.cpp \
    MainWindow/mainwindow.cpp
HEADERS += \
    ModifiedClasses/StatusBar.h \
    ModifiedClasses/TaskListView.h \
    Task/TaskTypes/Entry.h \
    Task/TaskTypes/MultipleChoice.h \
    Task/TaskTypes/OrderIndication.h \
    Task/TaskTypes/SingleChoice.h \
    Task/TaskTypes/Task.h \
    Task/TaskTypes/TaskView.h \
    Task/TaskTypes/Comparison.h \
    Task/TaskChoose.h \
    Task/TaskService.h \
    MainWindow/mainwindow.h \
    Task/TaskViewWidget.h \
    Test.h \
    ModifiedClasses/TestNameLine.h \
    ModifiedClasses/TextEdit.h
FORMS += \
    Task/TaskTypes/TaskView.ui \
    MainWindow/mainwindow.ui \
    Task/TaskViewWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
