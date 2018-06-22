###########################################################
# DLL Info Utility by Peter Schraut                       #
###########################################################

This file is part of PE Visual HAM !


"DLL Info Utility" is supplied as is.
The author disclaims all warranties, expressed or implied, 
including, without limitation the warranties of merchantability 
and of fitness for any purpose.

The author assumes no liability for damages, direct or 
consequential, which may result from the use of "DLL Info Utility".

This program uses a class called "TCEVersionInfo"
which is made by Evgeny Druzhinin.


###########################################################
# Whats it do                                             #
###########################################################

It shows information about a DLL file.

Here is what it shows:

File.............: cygwin1.dll
Filesize.........: 904008 Bytes
Company Name.....: Red Hat
File Description.: Cygwin« POSIX Emulation DLL
File Version.....: 1.3.12-cygwin-1-3-12-1
Internalname.....: cygwin1.dll
Legal Copyright..: Copyright ® Red Hat, Inc. 1996-2002
Legal TradeMarks.: Copyright ® Red Hat, Inc. 1996-2002
Original Filename: cygwin1.dll
Product Name.....: Cygwin
Product Version..: 1.3.12-cygwin-1-3-12-1
Comments.........: 1.3.12-cygwin-1-3-12-1
Major Version....: 1
Minor Version....: 3
Release..........:
Build............: 12-cygwin-1-3-12-1


###########################################################
# Usage                                                   #
###########################################################

Usage: DllInfo.exe [Switch] <File or Directory>


Switches:
          -h : Shows this help
          -f : Gets information from a single file
          -d : Scans a directory and shows information from each *.DLL
          -r : Scans a directory and all its subdirectories
               and shows information from each *.DLL

Example:
          DllInfo.exe -f c:\windows\system32\msjava.dll
          DllInfo.exe -d c:\windows\system32
          DllInfo.exe -r c:\windows


###########################################################
# Updates and Fixes                                       #
###########################################################

16/02/2003 - Initial Release

22/02/2003 - v0.2
             + Shows also the filesize now


###########################################################
# Website                                                 #
###########################################################

http://www.console-dev.de



+++ EOF +++