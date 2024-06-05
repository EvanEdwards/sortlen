#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "print_manpage.h"

#define INITIAL_BUFFER_SIZE 1024

typedef struct {
    char *line;
    size_t length;
} Line;

int compare(const void *a, const void *b) {
    const Line *lineA = (const Line *)a;
    const Line *lineB = (const Line *)b;
    return (lineA->length - lineB->length);
}

int compare_reverse(const void *a, const void *b) {
    const Line *lineA = (const Line *)a;
    const Line *lineB = (const Line *)b;
    return (lineB->length - lineA->length);
}

char *get_base_filename(char *path) {
    char *base = strrchr(path, '/');
    return base ? base + 1 : path;
}

void print_help(const char *prog_name) {
    const char *help_message =
        "Usage: %s [OPTIONS]\n"
        "Sort lines by length.\n\n"
        "Options:\n"
        "  -r                 Reverse the sort order.\n"
        "  -m min_chars       Set a minimum character limit for lines.\n"
        "  -d                 Ignore directories when considering length.\n"
        "  -x max_chars       Set a maximum character limit for lines.\n"
        "  -h, --help         Display this help message and exit.\n"
        "  --license          Display the license information and exit.\n"
        "  --man              Output the manpage as markdown and exit.\n"
        "                     See the EXAMPLES section to install manpage.\n"
        "  -q                 Suppress stderr output for -m and -x options.\n";
    printf(help_message, prog_name);
}

void print_license() {
    const char *license_message =
        "MIT License\n\n"
        "Copyright (c) 2024 Evan Edwards\n\n"
        "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
        "of this software and associated documentation files (the \"Software\"), to deal\n"
        "in the Software without restriction, including without limitation the rights\n"
        "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
        "copies of the Software, and to permit persons to whom the Software is\n"
        "furnished to do so, subject to the following conditions:\n\n"
        "The above copyright notice and this permission notice shall be included in all\n"
        "copies or substantial portions of the Software.\n\n"
        "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
        "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
        "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
        "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
        "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
        "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
        "SOFTWARE.\n";
    printf("%s", license_message);
}


char *read_line(FILE *fp) {
    size_t size = INITIAL_BUFFER_SIZE;
    char *buffer = malloc(size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    size_t len = 0;
    int c;
    while ((c = fgetc(fp)) != EOF && c != '\n') {
        if (len + 1 >= size) {
            size *= 2;
            buffer = realloc(buffer, size);
            if (!buffer) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
        buffer[len++] = (char)c;
    }
    if (c == '\n') {
        buffer[len++] = '\n';
    }
    buffer[len] = '\0';
    return buffer;
}

int main(int argc, char *argv[]) {
    int reverse = 0;
    int min_chars = 0;
    int max_chars = INITIAL_BUFFER_SIZE;
    int ignore_dirs = 0;
    int suppress_stderr = 0;
    int opt;
    int long_index = 0;

    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"license", no_argument, 0, 1},
        {"man", no_argument, 0, 2},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "rm:d:x:qh", long_options, &long_index)) != -1) {
        switch (opt) {
            case 'r':
                reverse = 1;
                break;
            case 'm':
                min_chars = atoi(optarg);
                break;
            case 'd':
                ignore_dirs = 1;
                break;
            case 'x':
                max_chars = atoi(optarg);
                break;
            case 'q':
                suppress_stderr = 1;
                break;
            case 'h':
                print_help(argv[0]);
                exit(EXIT_SUCCESS);
            case 1:
                print_license();
                exit(EXIT_SUCCESS);
            case 2:
                print_manpage();
                exit(EXIT_SUCCESS);
            default:
                print_help(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    Line *lines = NULL;
    size_t line_count = 0;
    size_t line_capacity = 0;

    while (!feof(stdin)) {
        char *buffer = read_line(stdin);
        if (strlen(buffer) == 0) {
            free(buffer);
            continue;
        }

        size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        char *line = strdup(buffer);
        char *compare_line = line;
        if (ignore_dirs) {
            compare_line = get_base_filename(line);
            len = strlen(compare_line);
        }

        if (len < min_chars) {
            if (!suppress_stderr) {
                fprintf(stderr, "%s\n", line);
            }
            free(line);
            free(buffer);
            continue;
        } else if (len > max_chars) {
            if (!suppress_stderr) {
                fprintf(stderr, "%s\n", line);
            }
            free(line);
            free(buffer);
            continue;
        }

        if (line_count >= line_capacity) {
            line_capacity = line_capacity == 0 ? 16 : line_capacity * 2;
            lines = realloc(lines, line_capacity * sizeof(Line));
            if (!lines) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }

        lines[line_count].line = line;
        lines[line_count].length = len;
        line_count++;
        free(buffer);
    }

    qsort(lines, line_count, sizeof(Line), reverse ? compare_reverse : compare);

    for (size_t i = 0; i < line_count; i++) {
        printf("%s\n", lines[i].line);
        free(lines[i].line);
    }
    free(lines);

    return 0;
}

