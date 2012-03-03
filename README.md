# nacl-safr

Google Chrome's Native Client module used by FileSafr that provides AES block cipher and SHA-1 hash.

## REQUIREMENTS

- [Python 2.7](http://www.python.org)
- [Scons 2.1.0](http://www.scons.org)
- [Google NaCL SDK](https://developers.google.com/native-client) with [Pepper17](https://developers.google.com/native-client/pepper17/)
- [TomCrypt library port to NaCL](http://code.google.com/p/naclports/)
- [depot_tools](http://dev.chromium.org/developers/how-tos/install-depot-tools)
- [gclient](http://code.google.com/p/gclient/)

## BUILD

```
$ export NACL_SDK_ROOT /path/to/naclsdk
$ export NACL_TARGET_PLATFORM pepper_17
$ ./scons
```

## SOURCE

This package can also be found on GitHub: https://github.com/FTSY/nacl-safr

## FOUND A BUG?

https://github.com/FTSY/nacl-safr/issues

## LICENSE

Copyright (c) 2012 FTSY

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.