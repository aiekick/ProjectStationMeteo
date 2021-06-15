QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    balise.cpp \
    baliseMer.cpp \
    baliseVille.cpp \
    balisevillepanel.cpp \
    datasMeteo.cpp \
    main.cpp \
    mainwindow.cpp
HEADERS += \
    balise.h \
    baliseMer.h \
    baliseVille.h \
    balisevillepanel.h \
    datasMeteo.h \
    mainwindow.h
FORMS += \
    balisevillepanel.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
