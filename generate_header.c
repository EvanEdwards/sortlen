#include <stdio.h>
#include <stdlib.h>

void escape_and_print_char(char c, FILE *out) {
    switch (c) {
        case '\n':
            fprintf(out, "\\n");
            break;
        case '\t':
            fprintf(out, "\\t");
            break;
        case '\r':
            fprintf(out, "\\r");
            break;
        case '\\':
            fprintf(out, "\\\\");
            break;
        case '\"':
            fprintf(out, "\\\"");
            break;
        default:
            if (c >= 32 && c <= 126)
                fputc(c, out);
            else
                fprintf(out, "\\x%02x", (unsigned char)c);
    }
}

int main() {
    char c;
    FILE *out = fopen("output.h", "w");
    if (!out) {
        perror("Failed to open output file");
        return 1;
    }

    fprintf(out, "#ifndef OUTPUT_H\n");
    fprintf(out, "#define OUTPUT_H\n\n");
    fprintf(out, "#include <stdio.h>\n\n");
    fprintf(out, "const char *file_contents = \"");

    while ((c = fgetc(stdin)) != EOF) {
        escape_and_print_char(c, out);
    }

    fprintf(out, "\";\n\n");
    fprintf(out, "void print_string() {\n");
    fprintf(out, "    printf(\"%%s\", file_contents);\n");
    fprintf(out, "}\n\n");
    fprintf(out, "#endif /* OUTPUT_H */\n");

    fclose(out);
    return 0;
}

