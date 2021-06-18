QT       += core gui network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GlobalSettings.cpp \
    LangManager.cpp \
    StyleManager.cpp \
    aboutdialog.cpp \
    balise.cpp \
    baliseMer.cpp \
    baliseMerPanel.cpp \
    baliseVille.cpp \
    balisevillepanel.cpp \
    datasMeteo.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdlg.cpp \
    widgetville.cpp

HEADERS += \
    GlobalSettings.h \
    LangManager.h \
    StyleManager.h \
    aboutdialog.h \
    balise.h \
    baliseMer.h \
    baliseMerPanel.h \
    baliseVille.h \
    balisevillepanel.h \
    datasMeteo.h \
    mainwindow.h \
    settingsdlg.h \
    widgetville.h

FORMS += \
    aboutdialog.ui \
    baliseMerPanel.ui \
    balisevillepanel.ui \
    mainwindow.ui \
    settingsdlg.ui \
    widgetville.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
    station_meteo_en.ts \
    station_meteo_fr.ts

RESOURCES += \
    res.qrc

