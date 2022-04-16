---
layout: base
title: honeysuckle README
---

honeysuckle
===========

A pure C library to make writing Lua bindings simple. honeysuckle provides
functions to make argument parsing, table operations, error creation and
handling, string wrangling, and registry operations easy and straightforward
from within your C code.

Table of contents
-----------------

- [Installation](#installation)
- [Documentation](#documentation)
- [Development](#development)
- [License](#license)
- [Footer](#footer)

Installation
------------

[(Back to top)](#table-of-contents)

honeysuckle requires CMake and the Lua 5.1 development files.

First, [download a honeysuckle release](/projects/honeysuckle/releases), 
and then do

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

You should now be able to include `<honeysuckle.h>` into your C 
files for use.

To make the tests as well, do the above and then do `make test`. 
To make the examples, do `make examples`.


Documentation
-----

You can view the honeysuckle documentation [on the honey wiki](https://honey3d.org/wiki/doku.php?id=honeysuckle).

Development
-----------
[(Back to top)](#table-of-contents)

honeysuckle is still very early in development. As the specifics of 
the build process and testing become clearer I'll update this 
section.

If you're interested in helping out, send me an email! The to-dos at 
the time of writing are:

* Write initial tests for errors, tracebacks, and function calling
* Implement everything
* Expand the test cases.

License
-------

[(Back to top)](#table-of-contents)


honeysuckle is licensed under the [Anti-Capitalist Software License].
Basically: if you're a single person, a co-op, or a nonprofit, feel free to
use this. Otherwise, send me an email. c:

[Anti-Capitalist Software License]: https://anticapitalist.software
