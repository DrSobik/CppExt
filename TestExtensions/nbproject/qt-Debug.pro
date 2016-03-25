# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = builds/Lin64bit/debug
TARGET = TestExtensions
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += ../RandExt/RandExt.cpp src/main.cpp src/test.cpp
HEADERS += ../Assignable/Assignable.h ../Clonable/Clonable.h ../Comparable/Comparable.h ../Exceptions/Exception.h ../Exceptions/MsgException.h ../Functor/Functor.h ../Include/Assignable ../Include/Clonable ../Include/Comparable ../Include/Exceptions ../Include/Functor ../Include/MathExt ../Include/Messages ../Include/Object ../Include/Operationable ../Include/RandExt ../Include/Runnable ../Include/SavableRestorable ../Include/SenderReceiver ../Include/Signals ../Include/SmartPointer ../Include/WritableReadable ../MathExt/MathExt.h ../Messages/Messages.h ../Object/Object.h ../Operationable/Operationable.h ../RandExt/RandExt.h ../Runnable/Runnable.h ../SavableRestorable/SavableRestorable.h ../SenderReceiver/SenderReceiver.h ../Signals/Signal.h ../SmartPointer/SmartPointer.h ../WritableReadable/WritableReadable.h src/test.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
UI_DIR = $$DESTDIR/ui
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += ../Include . 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
OBJECTS_DIR=$$DESTDIR/obj
