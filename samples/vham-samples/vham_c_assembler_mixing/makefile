#################################
# HAM Makefile
#################################

include $(HAMDIR)/system/master.mak

#
# Set the name of your desired GBA image name here
#
PROGNAME=demo

#
# Set a list of files you want to compile
#
OFILES += main.o myasm.o 

######################################
# Standard Makefile targets start here
######################################

all : $(PROGNAME).$(EXT) clean

#
# Most Makefile targets are predefined for you, suchas
# vba, clean ... in the following file
#
include $(HAMDIR)/system/standard-targets.mak

######################################
# custom  Makefile targets start here
######################################


gfx: makefile
	gfx2gba -D -fsrc -pbg.pal -t1 gfx/bg.bmp




