This folder holds the TeaTime++ tree containing the C++ implementation of TeaFiles.

TeaTime
=======
TeaTime is the productline of discretelogics that encompasses tools for time series persistence, processing and visualisation.

TeaFiles
========
TeaFiles are the low level persistence mechansim of TeaTime. For specification and details see discretelogics.com/teafiles .

Folder Structure
................

::

    - Bin               Examples and the Test application
      - Obj             Intermediate files
    - Examples          Source code of examples
    - Lib               boost, gtest, gmock dependencies (header + win32 binaries). remove if already available on your machine
    - TeaFile           Source code TeaFile API
    - TeaFile.Test	    Source code TeaFile tests (uses google gtest)
    Jamroot             *nix build file using Boost.Build.
    TeaFile.sln         Microsoft Visual Studio solution containing TeaFile library, tests and examples


Build
=====
Linux, Unix:
............

Use Boost.Build and run
::

  > bjam all
  or for the single projects
  > bjam TeaFile
  > bjam TeaFile.Test
  > bjam Sum
  > bjam AnalyzeTicks

On 32bit linux this create 32bit binaries, on 64bit linux 64bit binaries.
Consult the boost build manual for other parameters. 
  
Dependencies
............

- **boost libraries**: datetime and interprocess.
  since you will need boost.build, you will have to install the boost library anyway and can remove the Lib/boost folder

- **gtest** header and binary are required for the test application.

- **gmock**, not used yet, it will be used in the future

Windows
.......
  Open TeaFile.sln and choose one of the four configurations: debug/release 32/64bit. Binary dependencies gtest and boost are delivered    in the Lib folder, so the build should succeed without any further installation of these.

TeaFiles - C++ API
------------------
The TeaFile subfolder holds the C++ API provided as open source and licensed under the GPL . This API implements the TeaFile including fast data access via memory mapping.

TeaFiles.Test
-------------
A google gtest based unit test project. This is in progress, much better coverage tbd.

Examples
--------
Small examples demonstrate the usage of this api. Each of the projects references the TeaFile library.

Curent limitations
==================
1. **Text** - ASCII only
According to the specification, text strings are in UTF8. While the Windows version implements conversion between stirng with local encoding and UTF8 on both directions, the \*nix version does not yet implement this conversion. Since 7 bit ASCII is equals the first 127 characters of UTF8, this means that not special characters should be used.

2. **Time Format** - Java Time only
This API works only with a time format that counts Milliseconds since 1970/1/1, which is the resolution also used by Java, so we call it "Java Time". This is the recommended time format for versatile usage of TeaFiles.
