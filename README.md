# WiiMC for GameCube

This reworks WiiMC into a music player only, allowing it to work on the GameCube.

It has some different features compared to WiiMC:

# General Changes
* Based on WiiMC-SS v3.0.0
* Optimizes the GUI for low-mem usage.
* Uses FFmpeg FLAC (fixes seeking with controller, improves cover art reading)
* Forces MPlayer's high quality seeking for MP3.
* Adds a -Filter- option: Volnorm, Karaoke, Radio, Mono
* Cover art fade effect can be changed from the GUI.
* Banner screen saver doesn't care about file names.
* Single buffer version for less memory usage, may cause tearing.
* Only the gray theme, but it can be compiled with other themes.
* Only English and Spanish supported.

To make playback a nicer experience with the GC controller, it is possible to do more with it now.

After playing a file, hold the X button and use left/right to seek, L to seek to the beginning or R to end playback, up/down will both toggle pause.

You can press Z to view the credits screen, it will also display the available memory.

The banner screen saver can be a bit confusing to use, you need the artwork viewer enabled, as well as 'cover art on the screen saver' enabled, and you must also be on the video tab, this is the only purpose of the video tab now.


In the original WiiMC, multiple devices could be mounted at the same time, here it will only mount the first device it finds in the following order:

* GC-Loader / CUBEODE
* SD2SP2
* CARD Slot B
* CARD Slot A

It uses /apps/WiiMC/ to store settings.xml (in hindsight, a bad idea) it can collide with the original WiiMC so watch out for that.

Check out the video where I explain what lead me to work on this project.

# Video

[![Video backstory](https://img.youtube.com/vi/-EpUi2d2_VI/maxresdefault.jpg)](https://youtu.be/-EpUi2d2_VI)

# Known Issues

When compiling, you have to edit mplayer/Makefile to change the elf2dol path, I manually wrote the path and forgot to revert it.

Turning off the art viewer will not disable cover art reading (you just won't see it) this will be done eventually as it could make some files with huge artwork data unplayable. However, if you are on the video tab it won't read artwork since that memory is reserved for the banner screen saver.

While memory should be more than enough, mixing codecs can sometimes use up too much memory and crash, but I have tested a large folder with music for hours with no problems.

There is no BBA support and no ARAM support.

It has only been tested with a cubeode.
