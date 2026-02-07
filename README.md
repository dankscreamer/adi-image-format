A simple C library and tools for reading, writing, and converting ADI image files — a custom or binary image container format.

(Not to be confused with unrelated .ADI formats such as Active@ Disk Image backups or Amateur Data Interchange Format.)

About

This repository provides:

C source code to parse and emit ADI image format files.

Command-line utilities to read (read_adi) and write (write_adi) ADI image files.

A converter and test harness to explore ADI file contents.

A sample test.adi to demonstrate format usage.

The goal is to offer a lightweight, open implementation of the format for tools and workflows that need to manipulate ADI images in C.

Features

Read and display ADI image file contents.

Write ADI image files from raw data.

Convert between ADI and other representations (command tools).

Example ADI file included for experimentation.

Building

This project uses a Makefile for building and linking tools:

# Compile everything
make

# Clean build artifacts
make clean


This produces the following binaries:

read_adi — parse and show ADI image contents.

write_adi — create ADI image files.

Utility objects linked with the main library.

Usage
Reading an ADI File
./read_adi path/to/file.adi


Outputs the structure and pixel or metadata stored in the ADI file.

Writing an ADI File
./write_adi input_data output.adi


Converts raw image data into the ADI format.

(Details on input formats and flags should be added based on your data conventions.)

Format Overview

ADI here refers to a custom binary image container defined by this library.

Typical components might include:

Header with dimensions and pixel format

Image data blocks

Metadata chunks if any

(If ADI refers to a specific wider format you’re targeting, document specs here.)

Example
# Create from raw
./write_adi example.raw example.adi

# Inspect
./read_adi example.adi


Check test.adi for a known-good ADI file example.

Why It Exists

Developers working with ADI images need a free, open implementation to:

Inspect binary ADI files without proprietary tools.

Integrate ADI support into applications.

Learn the internal layout of ADI images for analysis or conversion.

Contributing

Contributions are welcome — improvements could include:

Better documentation of the format.

Support for additional image types and color spaces.

Tests against known ADI specs and files.

Porting to other languages or platforms.
