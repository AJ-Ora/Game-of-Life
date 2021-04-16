# Conway's Game of Life

Made in C++, using [wxWidgets](https://www.wxwidgets.org/) (version 3.0.5) for GUI rendering and [stb](https://github.com/nothings/stb) for loading images.

# How to build

## Windows

### Project tested on: Windows 10 (version 2004)

Clone the project. Do not open it yet!

Locate stable version 3.0.5 of [wxWidgets](https://www.wxwidgets.org/downloads/) (might work with later versions), and download the 64-bit version of the [development files](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxMSW-3.0.5_vc142_x64_Dev.7z) from pre-built binaries (link provided here points to the Visual Studio 2019 files).

For release build, [release DLLs](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxMSW-3.0.5_vc142_x64_ReleaseDLL.7z) are also required.

Unpack the development files, and copy everything inside the **"lib"** folder to the cloned project's **"lib"** folder. You will get a message, that some files already exist at the target location. Skip those files.

If you're using Visual Studio, first make sure you are able to create/open CMake projects. Then, open the project as a local folder.

Select "Game-of-Life.cpp" as the startup item, and build!

If you're getting error messages about missing DLLs, go to **"lib -> vc142_x64_dll"** and copy **"wxmsw30ud_core_vc142_x64.dll"** and **"wxbase30ud_vc142_x64.dll"** to the same directory where the built program is located at.

## Linux

### Project tested on: Debian 10

Clone the project.

You will need to download [wxWidgets' source code](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.5/wxWidgets-3.0.5.tar.bz2). Extract the downloaded package to any location.

Follow the instructions on [wxWidgets' wiki (Compiling and getting started)](https://wiki.wxwidgets.org/Compiling_and_getting_started) and build a shared (system-wide) library, or read the quick installation instructions listed below.

Make sure you have **"build-essential"**, **"cmake"**, **"libgtk2.0-dev"** and **"libgtk-3-dev"** installed.

To build wxWidgets, open up a terminal window, and enter these commands in order:

```
cd (location of extracted package)/wxWidgets-3.0.5/
mkdir gtk-build
cd gtk-build
../configure
make
sudo make install
sudo ldconfig
```

To build the cloned project, after successfully building wxWidgets, enter these commands in order:

```
cd (location of cloned project)/Game-of-Life/
mkdir out
cd out
cmake ..
make
```

You should now have **"Game-of-Life"** executable file in the **"out"** folder inside the cloned project's folder!
