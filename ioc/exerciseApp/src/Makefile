TOP=../..

include $(TOP)/configure/CONFIG

# build a host application

PROD_HOST  += caGet
caGet_SRCS += caGet.c
caGet_LIBS += $(EPICS_BASE_HOST_LIBS)

PROD_HOST  += caPut
caPut_SRCS += caPut.c
caPut_LIBS += $(EPICS_BASE_HOST_LIBS)

PROD_HOST      += caMonitor
caMonitor_SRCS += caMonitor.c
caMonitor_LIBS += $(EPICS_BASE_HOST_LIBS)

PROD_HOST          += caGetCompound
caGetCompound_SRCS += caGetCompound.c
caGetCompound_LIBS += $(EPICS_BASE_HOST_LIBS)


# ------------------------
# Build an IOC Application
# ------------------------

PROD_IOC = exercise

# exercise.dbd will be installed into <top>/dbd
DBD += exercise.dbd

# exercise.dbd will be created from these files
exercise_DBD += base.dbd
exercise_DBD += motorSupport.dbd
exercise_DBD += devSoftMotor.dbd
exercise_DBD += utilityLinux.dbd
exercise_DBD += asyn.dbd
exercise_DBD += stream.dbd
exercise_DBD += ecAsyn.dbd
exercise_DBD += calcSupport.dbd
exercise_DBD += drvAsynIPPort.dbd
exercise_DBD += pmacAsynMotorPort.dbd
exercise_DBD += pmacAsynIPPort.dbd
exercise_DBD += exercise6.dbd
#exercise_DBD += exercise7.dbd

# exercise_registerRecordDeviceDriver.cpp will be created
# exercise.dbd
exercise_SRCS += exercise_registerRecordDeviceDriver.cpp

exercise_SRCS += exerciseMain.cpp

# Add locally compiled object code
exercise_SRCS += exercise6.c
#exercise_SRCS += exercise7.stt

# This IOC Application depends on the following support modules
exercise_LIBS += motor
exercise_LIBS += softMotor
exercise_LIBS += asyn
exercise_LIBS += utility
exercise_LIBS += seq
exercise_LIBS += pv
exercise_LIBS += stream
exercise_LIBS += ecAsyn
exercise_LIBS += calc
exercise_LIBS += pmacAsynMotorPort
exercise_LIBS += pmacAsynIPPort
exercise_LIBS += $(EPICS_BASE_IOC_LIBS)

# Sequencer flags - re-entrancy
exercise_SNCFLAGS += +r

include $(TOP)/configure/RULES
