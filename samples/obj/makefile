#################################
# HAM Makefile
#################################

include $(HAMDIR)/system/master.mak

#
# Set the name of your desired GBA image name here
#
PROGNAME = obj

#
# Compile using Krawall software (set to yes or no) ?
# Also specify if Krawall is registered (yes or no)
#
USE_KRAWALL=yes
KRAWALL_IS_REGISTERED=no
KRAWALL_FILES= dq.s3m

#
# Set a list of files you want to compile 
#
OFILES += main.o module.o 

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


grfx: makefile
	gfx2gba -ogfx -t8 -D -fsrc gfx\\balls.bmp
	gfx2gba -ogfx -t1 -D -fsrc -pbg.pal  gfx\\bg.bmp




