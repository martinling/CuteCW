Cute CW: train yourself
=======================

# Build status
Debian build: ![](https://jenkins.sigpipe.me/job/cutecw-debian-build/badge/icon) Debian package AMD64: ![](https://jenkins.sigpipe.me/job/cutecw-binaries/architecture=amd64/badge/icon) Debian package ARMHF: ![](https://jenkins.sigpipe.me/job/cutecw-binaries/architecture=armhf/badge/icon) Windows Portable: ![](https://jenkins.sigpipe.me/job/cutecw-win32-portable/badge/icon)

# Introduction

  I've had thoughts for a long time about how we train ourselves in CW
  ("Carrier Wave" otherwise known as Morse Code).  After preparing for a
  presentation about learning CW I realized software could really help
  us out in ways not yet seen.  This is my effort to help decrease the
  pain in training your brain to understand Morse Code.

# History
  Cute CW was developed by WS6Z.
  Then merged Qt5 branch to master and made a lot of modifications by Dashie.

# Get it!

  You can download the source code or pre-built binaries from:
  - Debian / Ubuntu repository packages: https://bits.sigpipe.me/repos/debian/
  - Windows portable builds: https://bits.sigpipe.me/projects/CuteCW/
  - Source code: https://dev.sigpipe.me/DashieHam/CuteCW

# Further Information

  The growing list of [CHANGES](https://dev.sigpipe.me/DashieHam/CuteCW/src/master/docs/CHANGES.org) and the hopefully shrinking [TODO List](https://dev.sigpipe.me/DashieHam/CuteCW/src/master/docs/TODO.org)

# Compiling It

  CuteCW is a Qt5 based program.  That means to compile it you'll need
  some distribution of [Qt5](http://qt.nokia.com/).  You can download any of the recent Qt SDK
  sets and open the cutecw.pro file using qtcreator, which will then
  be able to compile and edit the code.  Or, if you want to compile it
  via a terminal you can try the following steps:

  1. edit cutecw.pro to enable portable build if needed (this will set config file to working dir of run app)
  2. qmake
  3. make
  4. lrelease cutecw.pro
  5. optionally: make install

  You can make a "portable" build (It will, as now, only check for configuration in directory where software is launched) by
  Un-commenting the line starting with "#DEFINES" with some comment above it in cutecw.pro

## Windows (copying with Qt Creator required libs to directory automatically"
  In Qt Creator, Project part :
  
  - Execute -> Deployment; Add custom step:
  - Command: windeployqt.exe
  - Args: --release --dir %{buildDir}\CuteCW_1.1_portable_win32 cutecw.exe
  - Working dir: %{buildDir}\release

  Build with or without the PORTABLE BUILD in cutecw.pro
  Then RUN the app from Qt Creator (it will call the deploy step)
  Then copy the following:
  - books to CuteCW_1.1_portable_win32
  - words to CuteCW_1.1_portable_win32
  - cutecw.cfg.sample to CuteCW_1.1_portable_win32\cutecw.cfg
  - Running "lrelease cutecw.pro" from Qt SDK to make .qm files
  - copying *.qm to CuteCW_1.1_portable_win32
  - from release dir : cutecw.exe to CuteCW_1.1_portable_win32
  
  Done, you have a portable build for Cute CW for windows in CuteCW_1.1_portable_win32

# Words List format
 For some Modes (actually: Word Training) the words list is dynamic using "words/mode/*.lst.txt" files, the format is simple :
  - First line is the short (two, threes words) description
  - rest of file is one word per line
  - filename doesn't matters but you can use the same description to sort them easily, also sorting is done by name so you can do 001_xxx.lst.txt 002_yyy.lst.txt etc.

 Word Training loads files from "words/wordtraining".

