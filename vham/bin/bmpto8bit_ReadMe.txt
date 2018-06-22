###########################################################
# Bitmap to 8bit Utility by Peter Schraut                 #
###########################################################

This file is part of PE Visual HAM !


"Bitmap to 8bit Utility" is supplied as is.
The author disclaims all warranties, expressed or implied, 
including, without limitation the warranties of merchantability 
and of fitness for any purpose.

The author assumes no liability for damages, direct or 
consequential, which may result from the use of "Bitmap to 8bit Utility".


###########################################################
# Whats it do                                             #
###########################################################
It reduces the colordepth of bitmap images (>8bit colordepth)
to 8bit colordepth 256 colors or any color amount you
specify.

The idea just came because sometimes i forget to export
bmp images as 8bit format and markus great converter (gfx2gba)
doesnt handle images > 8bit images. 

So from now on i, and you too, can just run bmpto8bit first 
and it will hopefully convert any bitmap image to 256 colors
or the color value you specified.

PS: The original reduce routine is done by Anders Melander.

###########################################################
# Usage                                                   #
###########################################################
bmpto8bit.exe [-r] <input file(s)>

Parameters:
-r : Specifies how many colors the image should have after
     reduction. This parameter will reduce the input image
     to the specified values. Pixels will map to their
     neariest paletteentry. Default=256 colors

Examples:
bmpto8bit.exe pic1.bmp
bmpto8bit.exe pic1.bmp pic2.bmp

bmpto8bit.exe pic1.bmp folder\*.bmp
bmpto8bit.exe *.bmp folder\*.bmp folder2\*.bmp



This will reduce pic1.bmp to 8 colors:
bmpto8bit.exe -r8 pic1.bmp

This will reduce pic1.bmp to 8 colors and pic2.bmp to 3 colors:
bmpto8bit.exe -r8 pic1.bmp -r3 pic2.bmp

This will convert each file to 16 colors:
bmpto8bit.exe -r16 *.bmp folder\*.bmp folder2\*.bmp

###########################################################
# Updates and Fixes                                       #
###########################################################

26/12/2002 - Initial Release
28/12/2002 - Function to reduce colors to a specified value


###########################################################
# Website                                                 #
###########################################################

http://www.console-dev.de



+++ EOF +++