DEBUG = y
XBE_TITLE = NevolutionX
SRCS += $(CURDIR)/main.cpp $(CURDIR)/outputLine.cpp $(CURDIR)/gameMenuItem.cpp \
	$(CURDIR)/menuItem.cpp $(CURDIR)/subsystems.cpp $(CURDIR)/findXBE.cpp \
	$(CURDIR)/renderer.cpp $(CURDIR)/folderparse.cpp $(CURDIR)/font.cpp \
	$(CURDIR)/xpadinput.cpp
NXDK_DIR = $(CURDIR)/../nxdk
NXDK_SDL = y
GEN_XISO = ${XBE_TITLE}.iso
include $(NXDK_DIR)/Makefile
