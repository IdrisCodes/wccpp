# wccpp
## __A wc wannabe application written in C++__

This is an implementation of the [wctool coding challenge](https://codingchallenges.fyi/challenges/challenge-wc) by John Crickett.

I tried to mimic wc's behaviour as closely as possible. Error messages/handling is still different though.
Also locale programming is a pita and probably doesn't work flawlessly.

If you dont have the boost libraries installed on your system, build might take too long. Sorry!

To build this application, you need:
- A compiler which supports C++ 17
- CMake 3.22 or later 

Also you will need an internet connection for CMake to download dependencies.

I have built this on x86-64, Ubuntu 22.04, using GCC 11.4.0

### Build
In the wccpp directory 
```
cmake -S . -B ./build/
cmake --build ./build/ --target wccpp --config Release
```

### Install
In the same directory
```
cmake --install ./build --prefix ~/ --config Release
```
This will copy the executable to ~/bin

Make sure to add this path to your PATH environment variable.
