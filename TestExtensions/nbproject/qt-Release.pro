# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = builds/Lin64bit/release
TARGET = TestExtensions
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += ../RandExt/RandExt.cpp src/main.cpp src/test.cpp
HEADERS += ../Acceptable/Acceptable.h ../Algorithm/Algorithm.h ../Assignable/Assignable.h ../Changeable/Changeable.h ../Clonable/Clonable.h ../Comparable/Comparable.h ../Driver/Driven.h ../Driver/Driver.h ../Exceptions/Exception.h ../Exceptions/MsgException.h ../Functor/Functor.h ../Include/Acceptable ../Include/Algorithm ../Include/Assignable ../Include/Changeable ../Include/Clonable ../Include/Comparable ../Include/Driver ../Include/Exceptions ../Include/Functor ../Include/MathExt ../Include/Messages ../Include/Object ../Include/Operationable ../Include/Parser ../Include/RandExt ../Include/Runnable ../Include/SavableRestorable ../Include/SenderReceiver ../Include/Signals ../Include/SmartPointer ../Include/Solver ../Include/Stopable ../Include/Variables ../Include/WritableReadable ../MathExt/MathExt.h ../Messages/Messages.h ../Object/Object.h ../Operationable/Operationable.h ../Parser/Parser.h ../RandExt/RandExt.h ../RandExt/RandExt_Interfaces.h ../RandExt/RandExt_LCG.h ../RandExt/RandExt_MersenneTwister.h ../Runnable/Runnable.h ../SavableRestorable/SavableRestorable.h ../SenderReceiver/SenderReceiver.h ../Signals/Signal.h ../SmartPointer/SmartPointer.h ../Solvers/Solver.h ../Stopable/Stopable.h ../Variables/Variables.h ../WritableReadable/WritableReadable.h src/test.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU_GCC5-Linux
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
UI_DIR = $$DESTDIR/ui
QMAKE_CC = gcc-5
QMAKE_CXX = g++-5
DEFINES += DEBUG 
INCLUDEPATH += . ../Include 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++14
}
OBJECTS_DIR=$$DESTDIR/obj
QMAKE_CXXFLAGS += -std=c++14
