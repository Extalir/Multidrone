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
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Barometro/BMP085.o \
	${OBJECTDIR}/CalcularImu.o \
	${OBJECTDIR}/Drone.o \
	${OBJECTDIR}/Funciones.o \
	${OBJECTDIR}/Gps.o \
	${OBJECTDIR}/I2C/I2Cdev.o \
	${OBJECTDIR}/MPU/MPU6050.o \
	${OBJECTDIR}/Magnometro/HMC5883L.o \
	${OBJECTDIR}/Motores.o \
	${OBJECTDIR}/PID.o \
	${OBJECTDIR}/PlanVuelo.o \
	${OBJECTDIR}/Serial.o \
	${OBJECTDIR}/Servidor.o \
	${OBJECTDIR}/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/multidrone_v_1_1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/multidrone_v_1_1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/multidrone_v_1_1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Barometro/BMP085.o: Barometro/BMP085.cpp 
	${MKDIR} -p ${OBJECTDIR}/Barometro
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Barometro/BMP085.o Barometro/BMP085.cpp

${OBJECTDIR}/CalcularImu.o: CalcularImu.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CalcularImu.o CalcularImu.cpp

${OBJECTDIR}/Drone.o: Drone.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Drone.o Drone.cpp

${OBJECTDIR}/Funciones.o: Funciones.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Funciones.o Funciones.cpp

${OBJECTDIR}/Gps.o: Gps.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gps.o Gps.cpp

${OBJECTDIR}/I2C/I2Cdev.o: I2C/I2Cdev.cpp 
	${MKDIR} -p ${OBJECTDIR}/I2C
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/I2C/I2Cdev.o I2C/I2Cdev.cpp

${OBJECTDIR}/MPU/MPU6050.o: MPU/MPU6050.cpp 
	${MKDIR} -p ${OBJECTDIR}/MPU
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MPU/MPU6050.o MPU/MPU6050.cpp

${OBJECTDIR}/Magnometro/HMC5883L.o: Magnometro/HMC5883L.cpp 
	${MKDIR} -p ${OBJECTDIR}/Magnometro
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Magnometro/HMC5883L.o Magnometro/HMC5883L.cpp

${OBJECTDIR}/Motores.o: Motores.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Motores.o Motores.cpp

${OBJECTDIR}/PID.o: PID.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PID.o PID.cpp

${OBJECTDIR}/PlanVuelo.o: PlanVuelo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PlanVuelo.o PlanVuelo.cpp

${OBJECTDIR}/Serial.o: Serial.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Serial.o Serial.cpp

${OBJECTDIR}/Servidor.o: Servidor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Servidor.o Servidor.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/multidrone_v_1_1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
