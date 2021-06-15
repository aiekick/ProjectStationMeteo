QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Singletons/GlobalSettings.cpp \
    src/core/balise.cpp \
    src/core/baliseMer.cpp \
    src/core/baliseVille.cpp \
    src/core/datasMeteo.cpp \
    src/gui/mainwindow.cpp \
    src/gui/settingsdlg.cpp \
    src/main.cpp

HEADERS += \
    src/Singletons/GlobalSettings.h \
    src/core/balise.h \
    src/core/baliseMer.h \
    src/core/baliseVille.h \
    src/core/datasMeteo.h \
    src/gui/mainwindow.h \
    src/gui/settingsdlg.h

FORMS += \
    src/gui/mainwindow.ui \
    src/gui/settingsdlg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
