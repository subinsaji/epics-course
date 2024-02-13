TOP=../..

include $(TOP)/configure/CONFIG

DATA += scanner.xml

include $(TOP)/configure/RULES

#----------------------------------------
#  ADD RULES AFTER THIS LINE

scanner.xml:
	$(ETHERCAT)/bin/$(T_A)/slaveinfo > chain.xml
	$(ETHERCAT)/etc/scripts/expandChain.py chain.xml > scanner.xml
