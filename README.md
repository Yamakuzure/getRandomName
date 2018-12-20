getRandomName
=======================================
Small console utility to generate random names using the PrydeWorX Library name
generator class.

The names generated are rather special, as they are not picked from random name
lists. Each name can consist of multiple parts, and each part is built by
combining syllables, that have been generated according to linguistic rules.

A possible output of five names with two parts and up to four syllables in each
part might be look like this:

```
./getrn -c 5 -P 2 -S 4
Natunada Westrya
Ilnere Ilam
Merryes Baia
Rynnor Eslano
Seblel Kor
```

This program is published under MIT license, which can be found in the dedicated
LICENSE file and at the end of this README.


Usage
---------------------------------------
The usage is quite simple, and explained using the `--help` argument.

The default behavior, when no options are given, is to write
one random name with 1-3 parts, 2-5 syllables and  6-15
characters to stdout.

```
  Options:
  -x,y,z,w      <value>    set value for the x,y,z or w coordinate. If
                           no offset is set, the program uses random ones
  -c --count    <count>    Generate <count> names
  -C --chars    <value>    Set maximum characters to generate.
  -h --help                Show this help and exit
    --mod<xyzw> <value>    set modifier for x, y, z or w coordinate
                           instead of using random ones (*)
  -n --norandom            Increase coordinates by 1 instead of
                           random modifiers. (*)
  -o --out      <filename> Write generated name(s) into
                           <file>.
  -P --parts    <value>    Set maximum parts to generate.
  -S --sylls    <value>    Set maximum syllables to generate.
  -s --seed     <value>    Set the seed to <value>.
  -v --version             Show program version and exit

(*) : Note on --mod* and --norandom:
      If you set at least one modifier, no random values will be used,
      but the value(s) you set, and 0.0 for all you omit. The --norandom
      option is only taken into account if you do not set any modifier
      and sets all four to 1.0.
```

Build and Install
---------------------------------------
Building and installation is done using make.

```
make
make install
```

See the `Makefile` for the options you have.


Prerequisites
---------------------------------------
 * `getRandomNames` depends on the latest PrydeWorX Library (pwxLib).  
   Get it at https://pwxlib.prydeworx.com


Contributing
---------------------------------------
To contribute to getRandomName, fork the current source code from
  [gitHub](https://github.com/Yamakuzure/getRandomName/).
Send a pull request for the changes you like.

If you want to report bugs, please do so at the getRandomName
  [issue tracker](https://github.com/Yamakuzure/getRandomName/issues)
on github.


License
---------------------------------------
MIT License

Copyright (c) 2010-2018 Sven Eden

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
