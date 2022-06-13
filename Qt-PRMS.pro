QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddRefMessBox.cpp \
    ModifyRefMessBox.cpp \
    PRMS.cpp \
    RefFile.cpp \
    Reference.cpp \
    admin.cpp \
    login.cpp \
    main.cpp \
    tinyXML/tinystr.cpp \
    tinyXML/tinyxml.cpp \
    tinyXML/tinyxmlerror.cpp \
    tinyXML/tinyxmlparser.cpp \
    visitor.cpp

HEADERS += \
    AddRefMessBox.h \
    Config.h \
    EditRefMessBox.h \
    ModifyRefMessBox.h \
    PRMS.h \
    RefFile.h \
    Reference.h \
    admin.h \
    login.h \
    tinyXML/tinystr.h \
    tinyXML/tinyxml.h \
    user.h \
    visitor.h

FORMS += \
    login.ui

msvc {
    QMAKE_CFLAGS += /utf-8
   QMAKE_CXXFLAGS += /utf-8
}

#msvc{
#    QMAKE_CFLAGS += -source-charset:utf-8
#    QMAKE_CXXFLAGS += -source-charset:utf-8
#}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
