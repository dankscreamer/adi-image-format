# ADI Image Format (v1)

ADI (Adit Image) is a simple raw image container format implemented in C.

The goal of this project was to understand:

- Binary file formats
- Struct layout and memory alignment
- File I/O in C
- Multi-file builds and linking
- Integrating third-party libraries
- Rendering raw pixel buffers using SDL2

This is not a compressed image format like PNG or JPG.  
ADI stores raw pixel data along with minimal metadata.

---

## 🧱 File Format (ADI v1)

An ADI file contains:

[ ADIHeader ][ Raw Pixel Data ]


### Header Structure

```c
struct ADIHeader {
    char magic[3];            // 'A', 'D', 'I'
    int width;                // Image width
    int height;               // Image height
    unsigned char channels;   // 1 (grayscale) or 3 (RGB)
};
After the header, pixel data is stored in row-major order:

R G B  R G B  R G B ...
🔁 Project Pipeline
This project implements a full image pipeline:

PNG/JPG
   ↓ (stb_image)
Raw pixels in memory
   ↓ (write_adi)
ADI file
   ↓ (read_adi)
Raw pixels
   ↓ (SDL2)
Window display
📦 Dependencies
Clang (or GCC)

SDL2

stb_image.h (included in project)

On macOS (Homebrew):

brew install sdl2
🔨 Build Commands
Build ADI Importer (Image → ADI)
clang -Wall -Wextra -std=c17 \
    write_adi.c read_adi.c adi_import.c \
    -o adi_import \
    `sdl2-config --cflags --libs`
Build ADI Viewer (ADI → Screen)
clang -Wall -Wextra -std=c17 \
    write_adi.c read_adi.c adi_view.c \
    -o adi_view \
    `sdl2-config --cflags --libs`
🚀 Usage
Convert PNG/JPG to ADI
./adi_import input.png output.adi
Example:

./adi_import testimg.png adit.adi

View ADI File
./adi_view adit.adi
A window will open displaying the image.

🧪 Testing
The project also includes a round-trip test:

pixels → write_adi → file → read_adi → pixels
This verifies byte-level correctness.

🎯 What This Project Demonstrates
Designing a binary file format

Managing memory ownership in C

Handling struct padding implications

Multi-file compilation and linking

Integrating third-party decoding libraries

Rendering raw pixel buffers using SDL2

📌 Limitations (v1)
No compression

No alpha channel support

Endianness not handled explicitly

Struct layout dependent on compiler

No encryption (planned for future version)

🙏 Credits
Image decoding powered by stb_image.h
https://github.com/nothings/stb

Rendering powered by SDL2
https://www.libsdl.org/

The SDL integration, README structuring, and architectural guidance were developed with assistance from AI tooling.

Testing

ADI v1 correctness is verified using a round-trip test:

pixels → write_adi → file → read_adi → pixels


The test checks:

Header equality

Byte-for-byte pixel equality

If the round-trip preserves data, the format is considered correct.

Portability Notes

ADI v1 assumes the same endianness between writer and reader

Struct layout is compiler-dependent

Future versions may add explicit versioning and fixed-width types

Versioning

This document describes ADI v1.

Future versions may:

Add a version field to the header

Add payload size or checksum

Add encryption metadata

Maintain backward compatibility where possible

Summary

ADI v1 is:

A raw image container

Simple, explicit, and testable

A stable foundation for future features

ADI v1 is complete.
