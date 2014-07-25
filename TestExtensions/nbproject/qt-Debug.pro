# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = TestExtensions
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += main.cpp
HEADERS += ../Assignable/Assignable.h ../Clonable/Clonable.h ../Comparable/Comparable.h ../Exceptions/Exception.h ../Exceptions/MsgException.h ../Functor/Functor.h ../Include/Assignable ../Include/Clonable ../Include/Comparable ../Include/Exceptions ../Include/Functor ../Include/MathExt ../Include/Messages ../Include/Object ../Include/Operationable ../Include/Runnable ../Include/SavableRestorable ../Include/WritableReadable ../MathExt/MathExt.h ../Messages/Messages.h ../Object/Object.h ../Operationable/Operationable.h ../Runnable/Runnable.h ../Savable/SavableRestorable.h ../SmartPointer/SmartPointer.h ../WritableReadable/WritableReadable.h SmartPointer
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += ../Include 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
