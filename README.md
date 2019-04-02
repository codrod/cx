  <h1>C Extensions</h1>
  <h3>Overview</h3>
  C Extensions, or CX for short, is a collection of extensions to the C programing language, packaged as a single shared library. These extensions include exception handling, automatic dynamic memory deallocation and destruction, a universal object interface, and generic containers. The library is written in C and is not hardware dependent. Currently only POSIX platforms are supported but a Windows port is planned. Please note that this project is still in the early stages of development.
  <h3>Documentation</h3>
  Documentation is generated using Doxygen and hosted on <a href="https://codrod.github.io/cx/index.html">GitHub Pages</a>.
  <h3>Build Instructions</h3>
  <ul>
    <li>make</li>
    <li>make examples</li>
    <li>make test</li>
    <li>make docs</li>
  </ul>
  <p>
    Running 'make test' will generate a script 'test.sh' which is used to start the automated unit testing.
  </p>
  <h3>Development Status</h3>
  <ul>
    <li>exception handling - completed</li>
    <li>memory management - completed</li>
    <li>strings - completed</li>
    <li>universal object interface - in progress</li>
    <li>generic containers - not started</li>
  </ul>
  <h3>Development Plan</h3>
  <ol>
    <li>Complete current features</li>
    <li>Improve documentation</li>
    <li>Optimize</li>
    <li>Windows port</li>
  </ol>
