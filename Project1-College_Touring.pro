QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    choosepath.cpp \
    database.cpp \
    login.cpp \
    main.cpp \
    mainWindow.cpp

HEADERS += \
    admin.h \
    choosepath.h \
    database.h \
    login.h \
    mainWindow.h

FORMS += \
    admin.ui \
    choosepath.ui \
    login.ui \
    mainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	img/Images.qrc

DISTFILES += \
	img/ChoosePath imgs/land-clipart-land-road-original.jpg \
	img/mainwindow imgs/college_tour_text.png \
	img/mainwindow imgs/mainwindow_picture.png \
	img/mainwindow imgs/mainwindow_picture.png
