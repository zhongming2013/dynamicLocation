#-------------------------------------------------
#
# Project created by QtCreator 2012-05-17T22:13:59
#
#-------------------------------------------------

QT       += core gui
QT       += core gui declarative   #for QML
QT       += sql  #for SQLite

TARGET = dynamicLocation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    win_qextserialport.cpp \
    qextserialport.cpp \
    qextserialbase.cpp \
    mapview.cpp \
    node.cpp \
    mapscene.cpp \
    employeeform.cpp \
    mobilenode.cpp \
    referencenode.cpp \
    employeeTableWidget.cpp \
    locationRecordForm.cpp \
    mobileTableModel.cpp \
    mobileTableView.cpp \
    serialportdialog.cpp \
    temperaturefrom.cpp \
    refertablemodel.cpp \
    refertableview.cpp

HEADERS  += mainwindow.h \
    win_qextserialport.h \
    qextserialport.h \
    qextserialbase.h \
    mapview.h \
    node.h \
    dbConnect.h \
    mapscene.h \
    employeeform.h \
    mobilenode.h \
    referencenode.h \
    employeeTableWidget.h \
    define.h \
    locationRecordForm.h \
    mobileTableView.h \
    mobileTableModel.h \
    serialportdialog.h \
    temperaturefrom.h \
    refertableview.h \
    refertablemodel.h

RESOURCES += \
    images.qrc

OTHER_FILES +=
