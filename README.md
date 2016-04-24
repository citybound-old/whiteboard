*This code is part of and developed for [Citybound](http://cityboundsim.com).
At some point in the future it might become stable and generally useful!*

# whiteboard

## Simple graphical console output

Imagine you could just print a small drawing to stdout - *whiteboard* makes this possible!

Just send special drawing commands to stdout and pipe your program to whiteboard.

**drawing.txt**
```
Whiteboard: ----
Whiteboard: arc 0.25 0.25 1 0 0.25 0.75
Whiteboard: arc 0.25 0.75 -1 0 0.25 0.25
Whiteboard: arc 0.5 0.25 1 0 0.5 0.75
Whiteboard: arc 0.5 0.75 -1 0 0.5 0.25
Whiteboard: color 0 0 0 64
Whiteboard: line 0.25 0.5 0.4 0.759808
Whiteboard: line 0.25 0.5 0.4 0.240192
Whiteboard: line 0.5 0.5 0.35 0.759808
Whiteboard: line 0.5 0.5 0.35 0.240192
Whiteboard: color 255 0 0 255
Whiteboard: dot 0.375 0.716506
Whiteboard: dot 0.375 0.283494
```
and then:

```
whiteboard < zeichnung.txt
```

will show the following window:

![](http://i.imgur.com/alwAWdY.png)

## Example applications

[compass](https://github.com/citybound/compass), the geometry library that Citybound uses. whiteboard is used here for additional graphical debug info in unit tests. Helper functions have been written to quickly write the correct drawing commands for compass'es geometric primitives, like lines, curves or circles.

## License

MIT, see [LICENSE.md](LICENSE.md) for details.
