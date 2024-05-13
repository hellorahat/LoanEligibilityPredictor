QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bulkeva.cpp \
    evaluate_data.cpp \
    load_data.cpp \
    main.cpp \
    mainwindow.cpp \
    singleeva.cpp

HEADERS += \
    bulkeva.h \
    evaluate_data.h \
    load_data.h \
    mainwindow.h \
    singleeva.h

FORMS += \
    bulkeva.ui \
    evaluate_data.ui \
    load_data.ui \
    mainwindow.ui \
    singleeva.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
