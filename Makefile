DEBUG = y
XBE_TITLE = NevolutionX
SRCS += $(CURDIR)/main.cpp $(CURDIR)/outputLine.cpp $(CURDIR)/gameMenuItem.cpp \
	$(CURDIR)/subsystems.cpp
#$(CURDIR)/doubleList.hpp
NXDK_DIR = $(CURDIR)/../nxdk
NXDK_SDL = y
GEN_XISO = ${XBE_TITLE}.iso
include $(NXDK_DIR)/Makefile
