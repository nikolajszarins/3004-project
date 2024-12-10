QT += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    pageprofileedit.cpp \
    pageprofileselect.cpp \
    pagerecord.cpp \
    pagerecordlist.cpp \
    pagetakereading.cpp \
    radotech.cpp \
    record.cpp \
    userprofile.cpp

HEADERS += \
    mainwindow.h \
    page.h \
    pageprofileedit.h \
    pageprofileselect.h \
    pagerecord.h \
    pagerecordlist.h \
    pagetakereading.h \
    radotech.h \
    record.h \
    userprofile.h

FORMS += \
    mainwindow.ui \
    pageprofileedit.ui \
    pageprofileselect.ui \
    pagerecord.ui \
    pagerecordlist.ui \
    pagetakereading.ui

LIBS += -lsqlite3

DISTFILES += users.db

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target