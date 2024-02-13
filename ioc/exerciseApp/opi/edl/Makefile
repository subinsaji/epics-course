TOP = ../../..
include $(TOP)/configure/CONFIG

DATA += $(patsubst ../%, %, $(wildcard ../*.edl))
DATA += $(patsubst ../%, %, $(wildcard ../*.gif))
DATA += $(patsubst ../%, %, $(wildcard ../*.png))
DATA += $(patsubst ../%, %, $(wildcard ../startgui*))

include $(TOP)/configure/RULES
