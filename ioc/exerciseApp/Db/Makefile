TOP=../..
include $(TOP)/configure/CONFIG

DB += $(patsubst ../%, %, $(wildcard ../*.db))
DB += $(patsubst ../%.vdb, %.db, $(wildcard ../exercise*.vdb))
DB += $(patsubst ../%.vdb, %.db, $(wildcard ../sim*.vdb))

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
