honey/gl
--------

only support 1 window, for simplicity

want to be **as transparent as possible**! only hide things from the Lua layer when they are either performance-critical or when they are so C-level that wrapping them would be too clunky.

**lua setup functions should do nothing except populate tables**

`gl.init()` will create the window (because that's how we get the opengl context)
