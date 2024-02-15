#!/scratch/wks59344/course/ioc/bin/linux-x86_64/exercise

## You may have to change exercise to something else
## everywhere it appears in this file

cd "/scratch/wks59344/course/ioc"

epicsEnvSet "STREAM_PROTOCOL_PATH", "/scratch/wks59344/course/ioc/data"

# Load binaries on architectures that need to do so.
# VXWORKS_ONLY, LINUX_ONLY and RTEMS_ONLY are macros that resolve
# to a comment symbol on architectures that are not the current
# build architecture, so they can be used liberally to do architecture
# specific things. Alternatively, you can include an architecture
# specific file.
# Commented out VxWorks command:ld < bin/linux-x86_64/exercise.munch

## Register all support components
dbLoadDatabase("dbd/exercise.dbd")
exercise_registerRecordDeviceDriver(pdbbase)

# Connect to the EtherCAT scanner
ecAsynInit("/tmp/scanner", 100000)

## Register all support components

exercise_registerRecordDeviceDriver(pdbbase)
drvAsynIPPortConfigure("MPS", "localhost:5002", 100, 0, 0)

## Load record instances
dbLoadRecords("db/exercise5.db","user=wks59344")

iocInit()

## Start any sequence programs
#seq &controlFilter,"user=wks59344"
