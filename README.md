![Logo from GDTF](content/logo.png)

# libMVRgdtf

**GDTF**: The `General Device Type Format` is an open standard for describing devices of the entertainment industry. These devices may be lighting fixtures, trusses, distribution boxes, media servers, lasers or other devices used in the entertainment industry. [This documentation](https://github.com/mvrdevelopment/spec/blob/main/gdtf-spec.md) describes [DIN SPEC 15800:2022-02](https://www.beuth.de/en/technical-rule/din-spec-15800/349717520) also known as GDTF, version 1.2.

**MVR**: The `My Virtual Rig` file format is an open standard which allows programs to share data and geometry of a scene for the entertainment industry. A scene is a set of parametric objects such as fixtures, trusses, video screens, and other objects that are used in the entertainment industry. [This documentation](https://github.com/mvrdevelopment/spec/blob/main/mvr-spec.md) describes [DIN SPEC 15801:2023-12](https://www.dinmedia.de/en/technical-rule/din-spec-15801/373968511) also known as MVR, version 1.6.



The GDTF file format is standardized in [DIN SPEC 15800:2022-02](https://www.beuth.de/en/technical-rule/din-spec-15800/349717520).

The MVR file format is standardized in [DIN SPEC 15801:2023-12](https://www.dinmedia.de/en/technical-rule/din-spec-15801/373968511).

## Current project status

The library currently supports all features of DIN SPEC 15800:2022-02 (GDTF 1.2), DIN SPEC 15801:2023-12 (MVR 1.6), and supports OSX, Windows, Linux, Android, and iOS.

## Building

Use CMake to build the project. Make sure XERCES variables are properly set.
You would need boost and xerces-c as dependencies.

A good example of how to build in on mac and win can be found in the GitHub Actions workflow file [libMVRgdtf/.github/workflows/build-static.yml](https://github.com/mvrdevelopment/libMVRgdtf/blob/master/.github/workflows/build-static.yml)


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

For help with GDTF and MVR file formats, visit [forum](https://gdtf-share.com/forum/) on the [GDTF Share](https://gdtf-share.com).

For help the library itself, [open an issue](https://github.com/mvrdevelopment/libMVRgdtf/issues/new/choose) here at Github.

## Contributing


## License

For the legal details, see the [LICENSE file](https://github.com/mvrdevelopment/libMVRgdtf/blob/master/LICENCE.md).
