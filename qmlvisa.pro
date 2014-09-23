TEMPLATE = lib
TARGET = QMLVisa
QT += qml quick
CONFIG += qt plugin

#message($$PWD)
#message("$$PWD/../../../Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/")

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.github.sedroca

# Input
SOURCES += \
    qmlvisa_plugin.cpp \
    qmlvisa.cpp \
    asrl.cpp \
    tcpip.cpp \
    usbraw.cpp \
    qmlvisaResourceManager.cpp

HEADERS += \
    qmlvisa_plugin.h \
    qmlvisa.h \
    asrl.h \
    tcpip.h \
    usbraw.h \
    qmlvisaResourceManager.h

OTHER_FILES = qmldir \
    AttributeInfo.txt

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

LIBS += $$quote(-Lc:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/) -lvisa32
INCLUDEPATH += $$quote(C:/Program Files/IVI Foundation/VISA/Win64/Include)
INCLUDEPATH += $$quote(c:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc)
DEPENDPATH += $$quote(c:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc)

#LIBS += $$quote(-LC:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc/) -lvisa32
#INCLUDEPATH +=$$quote(C:/Program Files (x86)/IVI Foundation/VISA/WinNT/include)
#DEPENDPATH += $$quote(C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc)
#DEPENDPATH +=$$quote(C:/Program Files (x86)/IVI Foundation/VISA/WinNT/include)

message(LIBSTR=$$LIBS)
message(INCPATH=$$INCLUDEPATH)
message(DEPPATH=$$DEPENDPATH)



