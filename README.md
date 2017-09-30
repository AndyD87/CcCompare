# CcDirectoryExport

Compare two directories and extract all differents in an extra output directory.

Execute following command for comparing two directories

    CcDirectoryExport [OriginalDir] [ModifiedDir] [OutputDir]

All files wich are new in ModifiedDir will be copied to **[Output]/new**
All files wich are deleted in ModifiedDir will be copied to **[Output]/deleted**
All files wich are different in ModifiedDir will be copied to **[Output]/modified**

# Build CcDirectoryExport

A little overview:
* Language: c++11
* Buildsystem: cmake

## Build on Windows

For building on Windows, at least Visual Studio 2013 is required, earlier Version doesn't fully support c++11.
In subdirectory "Tools", you can find some scripts for creating Solutions depending on Version and Architecture.
Direct builds with nmake are possbile. Look at cmake documentation, how to make it.

Execute following to get a Solution:

    cd Tools
    CmakeVS2013.x64.bat
    cd ..\Solution
    Main.sln
    
## Build on Linux

One way to build on Linux is to use building scripts under Tools:

    cd Tools
    build.sh # change to "buildDebug.sh" if debug is requried
    cd ..\Solution

Second way is to build on commandline, without build script.
Here an example:

    mkdir Solution
    cd Solution
    cmake ../
    make
    make install

## Licence

Author of CcDirectoryExport-Framework: (Andreas Dirmeier)[http://adirmeier.de]
This application is licenced under LGPL v3. Look at COPYING and COPYING.LESSER for further information.