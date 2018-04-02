Auto Tab Setup
==============

**As I have moved away from Windows as my main OS and Programmer's Notepad
appears to be more-or-less dead, I am no-longer maintaining Auto Tab Setup.**

Auto Tab Setup is a [Programmer's Notepad](http://www.pnotepad.org/) add-on which automatically configures the indent style and size to match the currently loaded text file.

Install
-------

Copy `Auto Tab Setup.dll` to `C:\Program Files (x86)\Programmer's Notepad` and run `pn --findexts` to register it with Programmer's Notepad.

Develop
-------

You'll need the following before you can start developing:

* [CMake](https://cmake.org/) in your PATH
* [Microsoft Visual C++](http://www.visualstudio.com/downloads/download-visual-studio-vs)
* The [Boost](http://boost.org/) C++ library
* The Programmer's Notepad SDK

Then, open a command prompt in the root of the project, set `BOOST_ROOT` to the location of Boost, `PN_SDK_DIR` to the Programmer's Notepad SDK directory and then run the following to generate the build files:

``` dos
mkdir build
cd build
CMake ..
```

Finally, you can open `build\Auto Tab Setup.sln` and get stuck in...
