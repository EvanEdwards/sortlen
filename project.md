---
name: sortlen
description: Sort lines by length
domain: sortlen
type: code
author: Evan Edwards
category: uncategorized
version: 0.0.3
---


![Header Image, a stack of paper and a title reading "sortlen, a simple cli utility"](hero.svg)

# sortlen

## Version {{version}}

A simple c utility that sorts lines by length.  Fully documented with a manpage.

# Installation

Clone or download the repo (hey, I'm not judging), and simply run `make install`

To create the man page you'll need pandoc, as the source is markdown.  The Makefile will ignorantly assume you have it and try to install.  Failure means that the man page won't be present, but -- assuming you have gcc -- you should still have the sortlen binary in your `$HOME/.local/bin`

If you don't want it there, move it elsewhere.  Or just run `make` and move `sortlen` where you want to from the bin directory, reading in `sortlen --man` how to manually install the man page.



