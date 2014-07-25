#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/TestKey.o \
	${OBJECTDIR}/AComparable.o

# Test Directory
TESTDIR=build/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/keys

dist/Debug/GNU-Linux-x86/keys: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/keys ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/TestKey.o: TestKey.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DEDEBUG -I/data/data/Projects/Common/Debug -MMD -MP -MF $@.d -o ${OBJECTDIR}/TestKey.o TestKey.cpp

${OBJECTDIR}/AComparable.o: AComparable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DEDEBUG -I/data/data/Projects/Common/Debug -MMD -MP -MF $@.d -o ${OBJECTDIR}/AComparable.o AComparable.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/test.o: tests/test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -DEDEBUG -I. -I/data/data/Projects/Common/Debug -MMD -MP -MF $@.d -o ${TESTDIR}/tests/test.o tests/test.cpp


${OBJECTDIR}/TestKey_nomain.o: ${OBJECTDIR}/TestKey.o TestKey.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/TestKey.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -DEDEBUG -I/data/data/Projects/Common/Debug -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/TestKey_nomain.o TestKey.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/TestKey.o ${OBJECTDIR}/TestKey_nomain.o;\
	fi

${OBJECTDIR}/AComparable_nomain.o: ${OBJECTDIR}/AComparable.o AComparable.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/AComparable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -DEDEBUG -I/data/data/Projects/Common/Debug -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/AComparable_nomain.o AComparable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/AComparable.o ${OBJECTDIR}/AComparable_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/keys

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
