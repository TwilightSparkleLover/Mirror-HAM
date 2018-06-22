#################################
# HAM Makefile
#################################

include $(HAMDIR)/system/master.mak

#
# Set the name of your desired GBA image name here
#
PROGNAME = demo

#
# Compile using Krawall software (set to yes or no) ?
# Also specify if Krawall is registered (yes or no)
#
USE_KRAWALL=yes
KRAWALL_IS_REGISTERED=no
KRAWALL_FILES= aqua.s3m autonomus.s3m ctgoblin.s3m explorat.s3m gmotion.s3m inspiration.s3m
#
# Set a list of files you want to compile
# (also put Krawall modules here)
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



