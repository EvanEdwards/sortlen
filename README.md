
![Header Image, a stack of paper and a title reading "sortlen, a simple cli utility"](hero.svg)

# sortlen

## Version  0.0.3

A simple c utility that sorts lines by length.  Fully documented with a manpage.

# Installation

Clone or download the repo (hey, I'm not judging), and simply run `make install`

To create the man page you'll need pandoc, as the source is markdown.  The Makefile will ignorantly assume you have it and try to install.  Failure means that the man page won't be present, but -- assuming you have gcc -- you should still have the sortlen binary in your `$HOME/.local/bin`

If you don't want it there, move it elsewhere.  Or just run `make` and move `sortlen` where you want to from the bin directory, reading in `sortlen --man` how to manually install the man page.

# Manual

## NAME
sortlen - sort lines by length

## SYNOPSIS
**sortlen** [OPTIONS]

## DESCRIPTION
The **sortlen** command sorts lines of text based on their length.  It reads from stdin and outputs to stdout, unless the line falls outside the specified filters, in which case the line goes to stderr.  Options may affect this behavior.  See below.

## OPTIONS
**-r**
:   Reverse the sort order.

**-m** *min_chars*
:   Set a minimum character limit for lines. Lines shorter than *min_chars* will be output to stderr.

**-x** *max_chars*
:   Set a maximum character limit for lines. Lines longer than *max_chars* will be output to stderr.

**-q**
:   Suppress stderr output for `-m` and `-x` options.

**-d**
:   Ignore leading directories in each line, only considering the base filename when determining length, but outputting the entire original line.

### Documentation options

**-h, --help**
:   Display this help message and exit.

**--license**
:   Display the license information and exit.

**--man**
:   Output the manpage as markdown and exit.

## EXAMPLES

### Basic Usage

Sort lines by length:

    $ ./sortlen < inputfile.txt

Sort lines by length in reverse order:

    $ ./sortlen -r < inputfile.txt

Sort lines and set a minimum character limit of 10 characters. Lines shorter than 10 characters are output to stderr:

    $ ./sortlen -m 10 < inputfile.txt

Sort lines and set a maximum character limit of 50 characters. Lines longer than 50 characters are output to stderr:

    $ ./sortlen -x 50 < inputfile.txt

Sort lines, ignoring leading directories in each line:

    $ ./sortlen -d < inputfile.txt

Suppress stderr output for lines outside character limits:

    $ ./sortlen -q -m 10 -x 50 < inputfile.txt

### Installing manpage

Display this manpage:

    $ ./sortlen --man |pandoc - -s -t man | /usr/bin/man -l -

Install this manpage locally:

    $ mkdir -p "$HOME/.local/share/man/man1" ; ./sortlen --man |pandoc - -s -t man >"$HOME/.local/share/man/man1/sortlen.1"

## LICENSE

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Notes

This utility has been written by Evan Edwards repeatedly over the decades.  This particular version was created to test ChatGPT in June 2024.  It did... okay.

