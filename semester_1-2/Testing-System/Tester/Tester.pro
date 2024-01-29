QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Task/TaskTypes/Entry.cpp \
    Task/TaskTypes/MultipleChoice.cpp \
    Task/TaskTypes/OrderIndication.cpp \
    Task/TaskTypes/SingleChoice.cpp \
    Task/TaskTypes/Task.cpp \
    Task/TaskTypes/TaskView.cpp \
    Task/TaskTypes/Comparison.cpp \
    Task/TaskViewWidget.cpp \
    Test.cpp \
    TestPassingWindow.cpp \
    TestResultWindow.cpp \
    main.cpp \
    mainwindow.cpp
HEADERS += \
    Task/TaskTypes/Entry.h \
    Task/TaskTypes/MultipleChoice.h \
    Task/TaskTypes/OrderIndication.h \
    Task/TaskTypes/SingleChoice.h \
    Task/TaskTypes/Task.h \
    Task/TaskTypes/TaskView.h \
    Task/TaskTypes/Comparison.h \
    Task/TaskService.h \
    TestPassingWindow.h \
    TestResult.h \
    TestResultWindow.h \
    mainwindow.h \
    Task/TaskViewWidget.h \
    Test.h
FORMS += \
    Task/TaskTypes/TaskView.ui \
    TestPassingWindow.ui \
    TestResultWindow.ui \
    mainwindow.ui \
    Task/TaskViewWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
