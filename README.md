C Extensions
============

### Overview

C Extensions, or CX for short, is a collection of extensions to the C programing language, packaged as a single shared library. These extensions include exception handling, automatic dynamic memory deallocation and destruction, a universal object interface, and generic containers. The library is written in C and is not hardware dependent. Currently only POSIX platforms are supported but a Windows port is planned. Please note that this project is still in the early stages of development.

### Documentation
    https://codrod.github.io/cx/index.html

### Build Instructions
* make
* make examples
* make test
* make docs

Running 'make test' will generate a script 'test.sh' which is used to start the automated unit testing.

### Status
* exception handling - completed
* memory management - completed
* strings - completed
* universal object interface - in progress
* generic containers - not started

### Development Plan
1. Complete current features
2. Improve documentation
3. Optimize
4. Windows port
