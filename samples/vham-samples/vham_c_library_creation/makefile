##########################################################################################
# HAM Makefile
#
# Created by Visual HAM V2 - Get Visual HAM at www.console-dev.de
#
##########################################################################################
include $(HAMDIR)/system/master.mak

#
# Set the name of your desired GBA image name here
#
PROGNAME=demo

#
# Set a list of files you want to compile
#
OFILES += main.o 

#
# Library Example:
#
# This will tell the compiler that we will add our Library called "mylib.a"
# which is stored into the folder "lib"
#
ADD_LIBS += lib/mylib.a

##########################################################################################
# Standard Makefile targets start here
##########################################################################################
all : $(PROGNAME).$(EXT) clean

#
# Most Makefile targets are predefined for you, suchas
# vba, clean ... in the following file
#
include $(HAMDIR)/system/standard-targets.mak

#
# Library Example:
#
##########################################################################################
#
# Specifies what files should become included
#
LIB_OFILES= mylib.o
# Target for building the library
#
lib: mylib.a clean
	rm -f mylib.s
#
#
mylib.a: $(LIB_OFILES)
	$(GCCARM)/arm-thumb-elf/bin/ar.exe rcs lib/$@ $(LIB_OFILES)
#
##########################################################################################


# END OF FILE
