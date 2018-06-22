Welcome to version of VisualBoyAdvance-SDL (0.8). This is a GB/GBC/GBA
emulator for Windows and Linux.

Changes for version 0.8:
------------------------

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
- Ctrl+R: reset
- Ctrl+P: pause
- F11: enter built-in debugger
- ESC: exit emulator

Options configuration
---------------------

All configurable options are accessible from the configuration file
VisualBoyAdvance.cfg. This file should be placed in the same directory
as the emulator or it should reside in the current directory where the
emulator is started from.

All options are documented in the file supplied with this distribution.

Command line options (override settings in configuration file)
--------------------------------------------------------------

  -F Full screen
  -b<bios file> Use given bios file
  -f<filter> Select filter:
   0 - normal mode
   1 - TV Mode
   2 - 2xSaI
   3 - Super 2xSaI
   4 - Super Eagle
  -d Enter debugger
  -s<frameskip> Set frame skip (0...5)
  -1 1x
  -2 2x
  -3 3x
  -4 4x

Default key setting
-------------------

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
