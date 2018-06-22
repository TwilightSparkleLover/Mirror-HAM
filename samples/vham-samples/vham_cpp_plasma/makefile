#################################
# HAM Makefile
#################################

include $(HAMDIR)/system/master.mak

#
# Set the name of your desired GBA image name here
#
PROGNAME=demo

#
# Compile using Krawall software (set to yes or no) ?
# Also specify if Krawall is registered (yes or no)
#
#USE_KRAWALL=no
#KRAWALL_IS_REGISTERED=no
#KRAWALL_FILES=

#
# Set a list of files you want to compile 
# 
OFILES += main.o bgpal.o

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
	gfx2gba -t8 -m -rs -ppart1.pal -fsrc -ogfx/part1/ gfx/part1/bg1.bmp gfx/part1/bg2.bmp
#	gfx2gba -t8 -m -pbg2.pal -A128 -fsrc -ogfx/part1/ gfx/part1/bg2.bmp	
	gfx2gba -t8 -D -fsrc -ogfx/part1/Sprite/ gfx/part1/Sprite/*.bmp		
	



