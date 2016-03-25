QT += core
QT += gui widgets

CONFIG += c++11

TARGET = TestExtensions
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

release{
    OBJECTS_DIR = release/obj
    MOC_DIR = release/moc
}

debug{
    OBJECTS_DIR = debug/obj
    MOC_DIR = debug/moc
}

SOURCES += \
    ../src/test.cpp \
    ../src/main.cpp \
    ../../Debug/DebugExt.cpp \
    ../../RandExt/RandExt.cpp

HEADERS += \
    ../src/test.h \
    ../../Assignable/Assignable.h \
    ../../Clonable/Clonable.h \
    ../../Comparable/Comparable.h \
    ../../Debug/DebugExt.h \
    ../../Exceptions/Exception.h \
    ../../Exceptions/MsgException.h \
    ../../Functor/Functor.h \
    ../../MathExt/MathExt.h \
    ../../Messages/Messages.h \
    ../../Object/Object.h \
    ../../Operationable/Operationable.h \
    ../../RandExt/RandExt.h \
    ../../Runnable/Runnable.h \
    ../../SavableRestorable/SavableRestorable.h \
    ../../SenderReceiver/SenderReceiver.h \
    ../../Signals/Signal.h \
    ../../SmartPointer/SmartPointer.h \
    ../../WritableReadable/WritableReadable.h

INCLUDEPATH += ../../Include
