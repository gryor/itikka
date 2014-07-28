Itikka
======

Itikka is a broadcasting radio repeater.

How does it work?
======
Itikka listens to radio transmissions creating and saving checksums of the received content.
If the received content's checksum is not found in it's history, the content
will be broadcasted.
History items will timeout to allow unchanged transmissions to be repeated.

How could it be used?
======
Itikka extends radio transmission distance as a man-in-the-middle node.

Hardware
======
I have tested Itikka on arduino pro micro with cheap radio receiver and
transmitter bought from ebay.
If other radio modules need to be used, please contribute to
https://github.com/wilhelmmatilainen/radio

How to build
======
I have not tested this with arduino ide. I'm building the project on linux using
ino like this:
```Shell
ino build -m micro
ino upload -m micro
```
