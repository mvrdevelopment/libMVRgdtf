# libMVRgdtf [![Build Status](https://travis-ci.com/DeerSoftDevelopment/libVectorworksMvrGdtf.svg?token=XYyJzkGhjzcyyYrPsJnY&branch=master)](https://travis-ci.com/DeerSoftDevelopment/libVectorworksMvrGdtf)
![Logo from GDTF](content/logo.png)

The General Device Type Format (GDTF) creates a unified data exchange definition for the operation of intelligent luminaires, such as moving lights. By creating a manufacturer-supported, unified standard, customers/users of lighting control systems, CAD systems, and pre-visualizers benefit by knowing the tools they use to perform their job will work consistently and dependably. The file format is developed using open source formats, and luminaire manufacturers in the entertainment design, production, and performance industries are welcome to use this open source technology.

The GDTF file format is standartisied in [DIN SPEC 15800](https://www.beuth.de/de/technische-regel/din-spec-15800/324748671).


## Current project status

The libary currently supports all GDTF 1.1 features and supports OSX, Windows, Linus and iOS.

## Building

Use CMake to build the project. Building should be as easy as:

```` bash
mkdir build
cd build
cmake ..
make
````

### Repository structure

### `./`

Contains all the project related files.

### `content/`

Contains media images used for the github page.

### `libs/`

Contains the libary.

### `shared/`

Contains `xerces`.

### `src/`

Contains the source code.

### `unittest/`

Contains all unit test related files.

## Where to get help

When you need help with the fileformat itself, go to the [forum](https://gdtf-share.com/forum/). 

When you need help with the libaray itself, please feel free to open an issue here at Github.

## Contributing


## License

For the legal details, see the LICENSE file.