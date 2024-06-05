#ifndef PRINT_MANPAGE_H
#define PRINT_MANPAGE_H

#include <stdio.h>

const char *manpage_contents = "---\ntitle: sortlen\nsection: 1\nheader: User Command\nfooter: Cheshire Hall, Evan \"JabberWokky\" Edwards <evan@cheshirehall.net>\nname: sortlen\ndescription: Sort by length of line\nauthor: Evan Edwards <evan@cheshirehall.net>\n---\n\n\n# NAME\nsortlen - sort lines by length\n\n# SYNOPSIS\n**sortlen** [OPTIONS]\n\n# DESCRIPTION\nThe **sortlen** command sorts lines of text based on their length.\n\n# OPTIONS\n**-r**\n:   Reverse the sort order.\n\n**-m** *min_chars*\n:   Set a minimum character limit for lines. Lines shorter than *min_chars* will be output to stderr.\n\n**-d**\n:   Ignore leading directories in each line, only considering the base filename when determining length, but outputting the entire original line.\n\n**-x** *max_chars*\n:   Set a maximum character limit for lines. Lines longer than *max_chars* will be output to stderr.\n\n**-h, --help**\n:   Display this help message and exit.\n\n**--license**\n:   Display the license information and exit.\n\n**--man**\n:   Output the manpage as markdown and exit.\n\n**-q**\n:   Suppress stderr output for `-m` and `-x` options.\n\n\n\n# EXAMPLES\n\n## Basic Usage\n\nSort lines by length:\n\n    $ ./sortlen < inputfile.txt\n\nSort lines by length in reverse order:\n\n    $ ./sortlen -r < inputfile.txt\n\nSort lines and set a minimum character limit of 10 characters. Lines shorter than 10 characters are output to stderr:\n\n    $ ./sortlen -m 10 < inputfile.txt\n\nSort lines and set a maximum character limit of 50 characters. Lines longer than 50 characters are output to stderr:\n\n    $ ./sortlen -x 50 < inputfile.txt\n\nSort lines, ignoring leading directories in each line:\n\n    $ ./sortlen -d < inputfile.txt\n\nSuppress stderr output for lines outside character limits:\n\n    $ ./sortlen -q -m 10 -x 50 < inputfile.txt\n\n## Installing manpage\n\nDisplay this manpage:\n\n    $ ./sortlen --man |pandoc - -s -t man | /usr/bin/man -l -\n\nInstall this manpage locally:\n\n    $ mkdir -p \"$HOME/.local/share/man/man1\" ; ./sortlen --man |pandoc - -s -t man >\"$HOME/.local/share/man/man1/sortlen.1\"\n\n\n# LICENSE\n\nMIT License\n\nPermission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n\n\n# Notes\n\nThis utility has been written by Evan Edwards repeatedly over the decades.  This particular version was created to test ChatGPT in June 2024.  It did... okay.\n\n\n";

void print_manpage() {
    printf("%s", manpage_contents);
}

#endif /* PRINT_MANPAGE_H */
