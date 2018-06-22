DynCon V0.1 (c) 2002+ Peter@Console-Dev.De
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Usage..: 
         DynConv.exe <Input File> <Output File> <Array Name> <Format File>

Example: 
         DynConv.exe picture.bmp picture.c arPicture c
or
         DynConv.exe picture.bmp picture.c arPicture c.fmt


Read below where the format files are stored.


What is DynConv?
~~~~~~~~~~~~~~~~

DynConv is another binary to include converter,
BUT it's not like the most converters on the net
which are only for a few formats.
It's a kind of "dynamic" converter, means
you can easily setup a new format for your
needs, without the need to code a new converter
or add any routines to an already existing converter.


I thought it's a pretty nice idea to have such a system
'cause i hate it always to search for a converter for
my needs or to extend the existing ;)




How do i setup a new format?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The format files (*.fmt) should be located into the
"formats" directory.

Directory structure to run DynCon properly:

Drive:\..\...
         formats
         +--+   
         |  +----asm.fmt
         |  +----c.fmt
         |  +----other *.fmt files
         |
         DynCon.exe


Just open one of the existing *.fmt files.
You'll see some "sections" hold into "{" and "}"


{START_PREFIX} = Anything what is between {START_PREFIX} and
                 {END_PREFIX} is written at the top of
                 the generated output file.
                 This section supports multiple lines.

{END_PREFIX}   = This is to let the "interpeting" system know
                 that this is the PREFIX section's end


{START_CONV}   = This stuff is for the converting routine itself.
                 Here will follow all the neccesary "options" what
                 the converter needs.

?FIRST?        = You can specify how the first byte of each row
                 should start.

?BYTE?         = This is to specify how the rest of the bytes 
                 (except the first and last one) should appear

?LASTBYTE?     = This specifies how the last byte should appear


?COUNT?        = Here you are able to specify the length of one
                 row. Means how many bytes you wish to
                 get in one single row.


{START_FINAL}  = This is to enter the final "section"
                 You can specify something what should be
                 added to the end of the output.
                 This section supports multiple lines.

?BYTE?         = This is to specify how the last byte of the file
                 should appear.

{END_FINAL}    = Exits the final section.




What variables can i use?
~~~~~~~~~~~~~~~~~~~~~~~~~

Well, it supports some, these are ...

%BYTE%         = Output is hex (e.g. for ff for 255)
%INT%          = Output is decimal

%ARRAYNAME%    = The specified arrayname
%FILENAME%     = The full filename of the file you convert
%FILEPATH%     = The absolute filepath of the file you convert
%FILESIZE%     = The filesize of the file you convert
%DATETIME%     = The actual Date and Time
%ONLY_FILENAME%= The filename (without path and without extension) of the file you convert
%FILEEXTENSION%= The fileextension of the file you convert



OK?! Lets do an example
~~~~~~~~~~~~~~~~~~~~~~~

I have choosed C/C++ :)

Ok here we go.

+++START OF FORMAT+++

{START_PREFIX}
/*
   Created on: %DATETIME%
   Sourcefile: %ONLY_FILENAME%
*/
#ifndef _%ARRAYNAME%_H
#define _%ARRAYNAME%_H
unsigned char %ARRAYNAME%[%FILESIZE%]=
{ 
{END_PREFIX}


{START_CONV}
?FIRST?=  
?BYTE?=0x%BYTE%,
?LASTBYTE?=0x%BYTE%,
?COUNT?=8
{END_CONV}


{START_FINAL}
?BYTE?=0x%BYTE%
};
#endif /* _%ARRAYNAME%_H */
{END_FINAL}

+++END OF FORMAT+++


Well, that's it!

Suggestions or bugs mailto peter@console-dev.de or
visit our site at www.console-dev.de and check if there
is any update available.

Thanks to Markus G. for the permission to use the formats of his bin2inc.


Releases and updates information
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

V0.1 - 08/28/02 - Initial release




