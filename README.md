# ADI Image Format (v1)

description: >
  ADI (Adit Image) is a custom raw image container format implemented in C.
  This project explores binary file format design, memory layout,
  file I/O, multi-file builds, third-party library integration,
  and rendering raw pixel buffers using SDL2.

---

## Overview

ADI is NOT a compressed format like PNG or JPG.

It stores:
  - Minimal metadata
  - Raw pixel data (RGB)

The project implements a full pipeline:

  PNG/JPG
      ↓ (stb_image)
  Raw Pixels (RAM)
      ↓ (write_adi)
  ADI File
      ↓ (read_adi)
  Raw Pixels
      ↓ (SDL2)
  Window Display

---

## ADI v1 File Layout

An ADI file consists of:

  [ ADIHeader ][ Raw Pixel Data ]

Header structure:

  struct ADIHeader {
      char magic[3];            // 'A', 'D', 'I'
      int width;                // Image width
      int height;               // Image height
      unsigned char channels;   // 1 (grayscale) or 3 (RGB)
  };

After the header:
  Pixel data is stored in row-major order:

  R G B  R G B  R G B ...

---

## Features

- Custom binary image container
- Round-trip read/write validation
- PNG/JPG importer
- SDL2-based viewer
- Multi-file C project structure
- Clean separation of format and tooling

---

## Dependencies

- Clang or GCC
- SDL2
- stb_image.h (included in project)

macOS (Homebrew):

  brew install sdl2

---

## Build Instructions

Build ADI Importer (Image → ADI):

  clang -Wall -Wextra -std=c17 \
      write_adi.c read_adi.c adi_import.c \
      -o adi_import \
      `sdl2-config --cflags --libs`

Build ADI Viewer (ADI → Screen):

  clang -Wall -Wextra -std=c17 \
      write_adi.c read_adi.c adi_view.c \
      -o adi_view \
      `sdl2-config --cflags --libs`

---

## Usage

Convert PNG/JPG to ADI:

  ./adi_import input.png output.adi

Example:

  ./adi_import testimg.png adit.adi

View ADI file:

  ./adi_view adit.adi

A window will open displaying the image.

---

## Testing

The project includes a round-trip validation:

  pixels → write_adi → file → read_adi → pixels

This ensures byte-level correctness.

---

## Limitations (v1)

- No compression
- No alpha channel support
- No explicit endian handling
- Struct layout dependent on compiler padding
- No encryption (future work)

---

## Learning Outcomes

- Binary file format design
- Struct memory layout implications
- Safe memory ownership patterns in C
- Linker and multi-file compilation understanding
- Third-party library integration
- Raw pixel rendering with SDL2

---

## Credits

Image decoding powered by:
  https://github.com/nothings/stb

Rendering powered by:
  https://www.libsdl.org/

SDL integration, README structuring, and architectural guidance
were developed with AI-assisted tooling.

---

## License

This project is intended for educational and experimental purposes.

