==================================================================
KRAWALL: NON-COMMERCIAL GCC SDK
Copyright (c) 2002 Sebastian Kienzl <seb at riot dot org>
http://mind.riot.org/krawall/
==================================================================

November 2002

Of course the "Final version" wasn't the last version of the free
SDK to be released, I should have known better.

What's new?
===========

Not much actually, I've backported a few fixes/enhancements
from the pay version to the free version.
This version of Krawall is contained in the latest HAM-release
(see http://www.ngine.de). A friendly hi to tubooboo.

- Fixed S3M-converter bug concerning pattern-order
- Updated DMA-code
- Updated the example's crt0 so kradInterrupt (Timer1) can't
  get interrupted when using multiple interrupts, see examples/crt0.s
- Added the up-to-date documentation. Note that not everything in
  the documentation might apply to the free version of Krawall.

So only the converter, the libs and the includes have changed --
example and docs are still the same.

==================================================================

September 2002, Final release

What's new?
===========

Final:
======
Somehow I must have included the wrong version of the library
in the last SDK, this version finally fixes the IWRAM-issues
for the free version.

Besides that not much has changed (for the free version at least).

There's the possibility to license Krawall online now.
The new Krawall-version is also available for non-commercial use and
is really affordable (currently $17).

Anyhow, I forgot to mention a few things in the previous releases:

- Please give me credit in your productions, if not in the production itself
  then at least in the accompanying info/documentation
- I'd appreciate it if you'd let me know when you've used Krawall,
  I'm always keen on seeing it in action!
- Send me a postcard if you liked the free version of the Krawall SDK to
  Sebastian Kienzl
  Steinickeweg 7
  80798 Munich
  Germany

Another thing, the documentation might not be fully up-to-date any more,
I don't maintain the docs for the free version any longer.

RC2:
====
I've made Krawall 'compatible' to GCC2 for these people
who are stuck with it (official nintendo-sdk for example).
Please read the readme.txt in the example-directory, it might
help you with getting the example to compile/work.

Besides I have fixed the memory usage for linkscripts that put
.data and .bss into IWRAM (most do that). I have simply forgotten
that fact so Krawall was actually using more memory than
specified in the docs. Note that this change hasn't made Krawall
slower.

Minor speed increase in mixing.

Krawall has been updated to replay XM's and use effects with
volume/pan-envelopes. These features are *not* available in this
non-commercial version.
==================================================================
This is the non-commercial version of Krawall, for commercial
use Krawall must be licensed.
For licensing information please contact me at seb@riot.org.

Please give me credit for Krawall in your productions,
if possible mention the webaddress.


TERMS OF USAGE

This distribution is provided as is without warranty of any kind.

I cannot be held liable for any damage arising out of the use or
inability to use this distribution.

You must not alter or redistribute this distribution.

This version of Krawall is for non-commercial use only:
For commercial use a license must be obtained.

By using this distribution you agree to these terms.
==================================================================
