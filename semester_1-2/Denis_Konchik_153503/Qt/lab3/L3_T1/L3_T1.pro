QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttons_settings.cpp \
    main.cpp \
    mainwindow.cpp \
    print_products.cpp \
    work_with_file.cpp \
    work_with_menu.cpp \
    work_with_sort.cpp

HEADERS += \
    mainwindow.h \
    node_list.h \
    product.h \
    productmenu.h \
    sortmenu.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
