QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GlobalSettings.cpp \
    balise.cpp \
    baliseMer.cpp \
    baliseMerPanel.cpp \
    baliseVille.cpp \
    balisevillepanel.cpp \
    datasMeteo.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdlg.cpp

HEADERS += \
    GlobalSettings.h \
    balise.h \
    baliseMer.h \
    baliseMerPanel.h \
    baliseVille.h \
    balisevillepanel.h \
    datasMeteo.h \
    mainwindow.h \
    settingsdlg.h

FORMS += \
    baliseMerPanel.ui \
    balisevillepanel.ui \
    mainwindow.ui \
    settingsdlg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
