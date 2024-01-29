QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttons.cpp \
    codeeditor.cpp \
    file_work.cpp \
    is.cpp \
    main.cpp \
    mainwindow.cpp \
    my_string.cpp \
    service.cpp

HEADERS += \
    codeeditor.h \
    mainwindow.h \
    my_pair.h \
    my_string.h \
    my_vector.h \
    structs.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-vector-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/release/ -lvector
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-vector-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug/ -lvector

INCLUDEPATH += $$PWD/../build-vector-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug
DEPENDPATH += $$PWD/../build-vector-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-vector-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/release/libvector.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-vector-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug/libvector.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-vector-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/release/vector.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-vector-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug/vector.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-string-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/release/ -lstring
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-string-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug/ -lstring
else:unix: LIBS += -L$$PWD/../build-string-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/ -lstring

INCLUDEPATH += $$PWD/../build-string-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug
DEPENDPATH += $$PWD/../build-string-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-string-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/release/ -lstring
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-string-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug/ -lstring

INCLUDEPATH += $$PWD/../build-string-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug
DEPENDPATH += $$PWD/../build-string-Desktop_Qt_6_2_3_MinGW_64_bit-Debug/debug
