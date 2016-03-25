# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux
TARGET = TestExtensions
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += ../RandExt/RandExt.cpp main.cpp test.cpp
HEADERS += ../Assignable/Assignable.h ../Clonable/Clonable.h ../Comparable/Comparable.h ../Exceptions/Exception.h ../Exceptions/MsgException.h ../Functor/Functor.h ../Include/Assignable ../Include/Clonable ../Include/Comparable ../Include/Exceptions ../Include/Functor ../Include/MathExt ../Include/Messages ../Include/Object ../Include/Operationable ../Include/RandExt ../Include/Runnable ../Include/SavableRestorable ../Include/SenderReceiver ../Include/Signals ../Include/SmartPointer ../Include/WritableReadable ../MathExt/MathExt.h ../Messages/Messages.h ../Object/Object.h ../Operationable/Operationable.h ../RandExt/RandExt.h ../Runnable/Runnable.h ../SavableRestorable/SavableRestorable.h ../SenderReceiver/SenderReceiver.h ../Signals/Signal.h ../SmartPointer/SmartPointer.h ../WritableReadable/WritableReadable.h test.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += DEBUG 
INCLUDEPATH += . ../Include 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
