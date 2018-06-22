#################################
# HAM Makefile
#################################

include $(HAMDIR)/system/master.mak

#
# Set the name of your desired GBA image name here
#
PROGNAME = transp

#
# Set a list of files you want to compile 
# 
OFILES += main.o 

######################################
# Standard Makefile targets start here
######################################

all : graphics $(PROGNAME).$(EXT) clean

#
# Most Makefile targets are predefined for you, suchas
# vba, clean ... in the following file
#
include $(HAMDIR)/system/standard-targets.mak

######################################
# custom  Makefile targets start here
######################################


graphics: makefile
	gfx2gba -t8 -M -fsrc -pobj.pal gfx\\buster.bmp
	gfx2gba -t8 -m -fsrc -pbg.pal  gfx\\balls.bmp gfx\\engine.bmp
	

	



