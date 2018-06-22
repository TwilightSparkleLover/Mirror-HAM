Welcome to version 1.0a of VisualBoyAdvance-SDL. This is a GB/GBC/GBA
emulator for Windows, Linux and BeOS.

Core changes:
- corrected sound mixing to be more like in version 0.9.1

Features:
---------

- configurable GB/GBA keys, including joystick support
- option to use BIOS file
- directory selection for save state, battery and screen capture
- fullscreen mode
- video sizes 1x, 2x, 3x and 4x
- graphic filters Normal, TV Mode, 2xSaI, Super 2xSaI and Super Eagle
- same emulation core as VisualBoyAdvance: GB and GBA emulation
- built-in ARM/THUMB assembly debugger
- 10 save states accesible through keyboard
- automatic battery file load/save
- auto-fire support
- pause, reset through keyboard
- 16, 24 and 32 bit desktop support
- GDB remote debugging (see below for information)


Installing
----------

The easiest installation is to place all files in the distribution in the
same directory.

Support
-------

Please support VisualBoyAdvance by making a donation. You can donate money
using PayPal (www.paypal.com). Send donations to vb@emuhq.com. If you want
to make other kind of donations (hardware, etc...), please contact me.

System requirements
-------------------

Windows: PIII 500Mhz machine for GBA emulation. GB emulation requires far less.

Linux: minimum requirement should be similar to Windows version. SDL 1.2.2
       runtime library must be installed prior to running the program. You can
       download it from http://www.libsdl.org

Key combinations during emulation:
----------------------------------

- F1...F10: load save state 1...10
- Shift+F1...F10: save state 1...10
- Alt+1...4: auto-fire A,B,L,R
- Ctrl+1...8: enable/disable graphical layers (BG0, BG1, BG2, BG3, OBJ, WIN0,
  WIN1, OBJWIN)
- Ctrl+N: pause on next frame
- Ctrl+R: reset
- Ctrl+P: pause
- F11: enter built-in debugger
- ESC: exit emulator

Emulation key settings:
-----------------------

- Movement: arrow keys
- Button A: Z
- Button B: X
- Button L: A
- Button R: X
- Button Start: ENTER
- Button Select: BACKSPACE
- Speed up: SPACE
- Screen capture: F12
- Motion Left: NUMPAD 4
- Motion Right: NUMPAD 6
- Motion Up: NUMPAD 8
- Motion Down: NUMPAD 2


GDB support
-----------

VisualBoyAdvance now provides GDB remote debugging support. This gives
developers the full power of GDB to debug GBA applications.

In order to use this, you will need a cross-compiled GDB for either the arm-elf
or arm-thumb-elf target (used for the --target= option of GDB configure
script).

You can also use GDB frontends like DDD, CodeMedic, etc... or even GDB/Insight
for GUI debugger (if using anything other than GDB/Insight, please make sure
to point to the right GDB executable).

The emulator provides two transport protocols for remote debugging:

- TCP: allows debugging through TCP using port 55555 (or any specified) port.
  The advantage of using TCP is that it allows true remote debugging but it is
  slower compared to the pipe method (pipe method does not work on Windows -
  probably a restriction imposed by the CYGWIN port of GDB).
- PIPE: allows debugging through a PIPE between the emulator and GDB. This is a
  lot faster than TCP and recommened on Unix systems.

Using TCP transport
-------------------

To use the TCP transport, use the flag -Gtcp[:portnum] where portnum is an
optional port number to be used instead of 55555. VBA will wait for a GDB
connection on the specified port (printed on screen). Start GDB by passing the
.elf file, then connect to the emulator by using the command:

target remote <hostname>:<port number>

where hostname is the host where the emulator is running and port number is the
printed port number.

Using PIPE transport
--------------------

To use the PIPE transport, start GDB with the .elf file to be debugged. Connect
to the emulator by using the command:

target remote |<full path to VBA>/VisualBoyAdvance -Gpipe

Debugging with GDB
------------------

Once you connected to the emulator, you can set breakpoints and debug the
application. But before doing that, you will need to issue the loda command on
GDB to load the code into the emulator. Optionally, you can pass the ELF file
on the emulator's command line (along with the -N option to not parse the debug
information in the emulator) instead of issuing the load command.

After connecting and optionally loading the file into the debugger, you can
start debugging: add breakpoints, step, etc...

While using GDB, any console output (see below) will show up in GDB's console.

If you want to break into the GDB, press F11 and it will give you full command
in GDB again. Pressing ESC will terminate emulation.

You can also detach GDB from the emulator.


Console Output
--------------

There are two forms of console output in this version:

- Mappy style dprint: use the following code (from Mappy's documentation) to get
  output:

- VBA style: use the following code to get output:
  // THUMB code
  void print(char *s)
  {
    asm volatile("mov r0, %0;"
                 "swi 0xff;"
                 : // no ouput
                 : "r" (s)
                 : "r0");
  }
  // ARM code
  void print(char *s)
  {
    asm volatile("mov r0, %0;"
                 "swi 0xff0000;"
                 : // no ouput
                 : "r" (s)
                 : "r0");
  }

When using GDB, the output will show up in GDB's console. When using the built-in
debugger, output will go to standard out.

Built-in debugger enhancements
------------------------------

The built-in debugger has the following enhancements (need debug enabled ELF
file):
- ELF file support: both multiple and regular. Please report any messages or
  problems reading ELF files. C++ classes and some miscellaneous features are
  not supported yet. Also, method names may be mangled in C++ code.
- break command: add a breakpoint on a function, line number of file:line
  number
- locals command: print the local variables on the current function
- print command: prints the value of a given expression. Valid expression
  include *this, ptr->member, var.member, array[0], sizeof(expression), etc...
- symbols command: list information known about a symbol (or symbols that start
  with the given name)
- radix command: sets the output radix to eithe decimal, octal or hex.
- file and line number when stopped: the debugger will show the file and line
  number (if available) for the current address
- fixes to some breakpoint handling problems
- fixes to break on write function

Options configuration
---------------------

All configurable options are accessible from the configuration file
VisualBoyAdvance.cfg. This file should be placed in the same directory
as the emulator or it should reside in the current directory where the
emulator is started from.

All options are documented in the file supplied with this distribution.

Command line options (override settings in configuration file)
--------------------------------------------------------------

  -1 1x
  -2 2x
  -3 3x
  -4 4x
  -F Full screen
  -G<protocol> GNU Remote Stub mode:
    tcp        - use TCP at port 55555
    tcp:<port> - use TCP at port <port>
    pipe       - use pipe transport
  -N Don't parse debug information
  -Y<type> Use YUV overlay for drawing:
    0 - YV12
    1 - UYVY
    2 - YVYU
    3 - YUY2
    4 - IYUV
  -b<bios file> Use given bios file
  -d Enter debugger
  -f<filter> Select filter:
    0 - normal mode
    1 - TV Mode
    2 - 2xSaI
    3 - Super 2xSaI
    4 - Super Eagle
    5 - Pixelate (experimental)
    6 - Motion Blur (experimental)
  -s<frameskip> Set frame skip (0...5)
  -v<verbose> Set verbose level (add flags values for multiple):
    1 - SWI
    2 - Unaliagned memory access
    4 - Illegal memory write
    8 - Illegal memory read

Known bugs
----------

- loading a save state that uses a different sound quality may hang the
  emulator. Please only use the 22Khz sound quality save states from the
  Windows version with this release
- built-in debugger still has a few bugs
- disassembler contains a few errors. Please report anything wrong you find

Warranty
--------

VisualBoyAdvance-SDL comes with no warranty. Use it at your own risk.

Contact
-------

Please don't email unless you found some bug. Requests will be ignored and
deleted. Also, be descriptive when emailing. You have to tell me what version
of the emulator you are writing about and a good description of the problem.
Remember, thre is a SDL version, a Windows version and a Linux version. Also,
there are still people writing about the old VisualBoy which is no longer
supported. Also remember I am not paid to work on VisualBoyAdvance. This is
just a hobby.

Forgotten (vb@emuhq.com)
http://vboy.emuhq.com

Special Thanks
--------------

Costis for his help fixing some of the graphics bugs.
Snes9x developers for the great emulator and source code.
Kreed for his great graphic filters
SDL team for this amazing library
And all users who kindly reported problems.

Change History
--------------

Version 1.0a:

Core changes:
- corrected sound mixing to be more like in version 0.9.1

Version 1.0:

Core changes:
- semi-transparent objects are now processed correctly when windows enabled
- battery files now written even after resetting
- 16-bit sound rendering
- fixed some LDM/STM instructions when running in user/system mode
- added missing LDM/STM instruction formats
- Div/DivARM BIOS calls work correctly when dividing by 0
- added sound echo effect
- added sound low pass filter
- added reverse stereo support
Gameboy changes:
- can now edit palette for mono games
SDL changes:
- fixed autofire for L/R buttons (was not working before)
- added support for sound quality selection

Version 0.9.1:

Core changes:
- fixed BG2CNT corruption in some cases
- fixed rendering of sprites with invalid OBJ Mode
- fixed 32-bit access to some IO registers
- fixed some unknown messages when loading ELF files
- fixed small error when doing a 16-bit write to palette RAM
- fixed minor bug in CpuFastSet emulation
- fixed some crashes loading GCC 3.0.4 ELF files
- fixed minor problem with CPSR (to be consistent with documentation)
- added single frame stepping (pauses after drawing the next frame)
- BMP screen capture option
SDL changes:
- added development logging option (bios usage, illegal read, illegal writes)
- call stack information (GCC 3+ (ARM mode only) or ARM SDT)

Version 0.9a:

Core changes:
- fixed rotation screen bug introduced in version 0.9
- fixed some memory write corruption

Version 0.9:

Core changes:
- support for enabling/disabling graphical layers
- correct sound channel 4 emulation
- support for multiboot files (.MB)
- support for ELF files
- fixed some memory leaks
- fixed LDM/STM instructions (missing formats and wrong behaviour - littleos
  now works)
- fixed PUSH/POP instructions
- fixed misaligned half word reads
- fixed invalid memory reads
- fixed IO memory readability and register writing
- fixed HuffUnComp missing last bytes bug
- fixed a small DMA bug
- fixed bug in rotation screens (hoffset demo works again)
Gameboy changes:
- correct sound channel 4 emulation
- fixed bug reading joypad when LCD is off
- fixed small bug in SGB code
- fixed bug in SGB Block command
SDL changes:
- GDB remote debugging support (see Readme of SDL version for details)
- YUV support (courtesy of Niels Wagenaar)
- improvements to embedded debugger (locals, break, print, symbols commands)
- console output support (Mappy style and a new one)
- partial ELF support in the internal debugger
- support for HAT buttons

Version 0.8:

Core changes:
- correctly initializing IO registers when running without BIOS(Gollum/Costis)
- support for GSA ROM patching codes and button codes
- support for CodeBreakerAdvance codes
- support for separate frameskip for GBA and GB roms
- reworked the cheat system internal (should improve speed a bit)
- added a small interrupt latency to avoid interrupt loop
- fixed 16-bit DMA transfers with decrement options
- fixed semi-transparent OBJ bug
- fixed Gameshark Advance snapshot import
- fixed crash when passing filename without a path on command line
- fixed ARM LDR/STR with ASR shifted register instructions
- fixed some disassembly bugs
- fixed sound mixing (reversed sound)
- fixed misaligned 16-bit reads
Gameboy changes:
- fixed sound mixing (reversed sound)
- fixed vertical scrolling bug (Kefren bars demo)
- fixed speed up bug changing sound quality during emulation
SDL changes:
- added command line flag for frameskip
- added command line support for bios file
- fixed configuration file comments on control configuration

Version 0.7.1:

Core changes:
- sound scratch problem fixed
- sound mixing improved
- sound channel 3 new function added
- Gameshark code support fixed for some codes
- all cheat codes are validated for wrong characters
- 64k EEPROM support
- added BIOS calls protection for BIOS memory area
- fixed problem with stop mode and loading a save state
- fixed window behaviour on some undocumented cases (thanks mrquackers)
SDL version:
- fixed debugger disassembled line when on breakpoint
- fixed loading a state with a different sound quality (quality doesn't change)

Version 0.7a:

- fixed slowdown/graphic sync problem
- fixed x4 problem
- enabled experimental graphic filters: pixelate and motion blur (config file
  or through command line)
- added BIOS calls Stop, IntrWait and SoundBiasReset (missing from 0.7 changes)
- fixed the disassembler commands parsing when passing instruction count
- added usage messages when missing argument to call

Version 0.7:

Core GBA emulation:
- emulating GBA windows correctly when they wrap around the screen
- fixed some minor THUMB flag bugs
- fixed blended sprites priority bug
- fixed unimplemented ARM LDM opcode
- not applying SFX to semi-transparent sprites
- completed mode 5 emulation
- disable sfx now takes effect immediately
- screen capture sets the correct extension when name typed
- MOSAIC support in all video modes and sprites
- fixes to several of the reported black screen, hangs and missing opcode
- Gameshark code support
- import function for battery files, code files and game saves
- export function for battery files
Core GB emulation:
- fixed window priority bug (sprites on top of window)
- screen capture now being taken before status message is displayed
- import function for battery files, code files and game saves
- export function for battery files (no RTC saved in this case)
SDL versions:
- fixed some small disassembler bugs
- fixed keyboard shortcuts with modifier keys (Ctrl, Alt, Shift)
- added MMX support (default is off)
- configuration file now in DOS format for the Windows version
- added break on write support for IRAM and WRAM
Linux version specific:
- fixed some bad opcodes
