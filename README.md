# TactonLibrary
Arduino library + host PC library + GUI for debugging

# Compiling

On VSCode, please use the C/C++ Extension pack. Compiling uses CMake, tested on Mac so far.

This code uses a submodule for serial communications, use `git submodule init ; git submodule update` to get it.

Applications need Qt6, installed on mac with `brew install qt`.
