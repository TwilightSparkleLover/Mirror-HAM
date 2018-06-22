#################################
# HAM Makefile
#################################


include $(HAMDIR)/system/master.mak

#
# Set the name of your desired GBA image name here
#
PROGNAME = map

#
# Set a list of files you want to compile 
#
OFILES += main.o 

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

modfile.o: module.mod
	ld -A elf32-littlearm --format binary --oformat elf32-littlearm module.mod -o modfile.o -r -EL -T $(LIBDIR)/bin2rodata.x

gfx: makefile
	gfx2gba -t8 -m -fsrc gfx\\*.bmp
	gfx2gba -t8 -m -rs -fsrc gfx\\facerot.bmp
	



