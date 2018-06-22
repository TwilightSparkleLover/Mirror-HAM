###########################################################
# HighColor Gfx Converter by Peter Schraut                #
###########################################################

This file is part of PE Visual HAM !


"HighColor Gfx Converter" is supplied as is.
The author disclaims all warranties, expressed or implied, 
including, without limitation the warranties of merchantability 
and of fitness for any purpose.

The author assumes no liability for damages, direct or 
consequential, which may result from the use of "HighColor Gfx Converter".


###########################################################
# Whats it do                                             #
###########################################################

This program converts a bitmap file either int an 1D array
ot into a 2D C/C++ array.

Each value represents the color value in 15bit BGR format of
the pixel located at x,y

###########################################################
# Usage                                                   #
###########################################################

Usage: hcgfx.exe [-mode] <bitmap file>

Modes:
       -1d  :  Create 1D c/c++ array
       -2d  :  Create 2D c/c++ array

###########################################################
# Updates and Fixes                                       #
###########################################################

12/01/2003 - Initial Release
15/02/2003 - Added "#define" stuff
21/03/2003 - Added function to create also an 1D array

###########################################################
# Website                                                 #
###########################################################

http://www.console-dev.de



+++ EOF +++