#!/bin/bash

# Default values
header_filename="print_string.h"
function_name="print_string"
variable_name="print_string_value"

# Helper function to print usage
usage() {
    echo "Usage: $0 [-h HEADER_FILENAME] [-f FUNCTION_NAME] [-v VARIABLE_NAME] [TEXT_FILE]

    TEXT_FILE            Input text file, or reads from stdin.

If a text file is provided, the naming is derived from that.  If stdin, it is print_string.

These values may be overridden via the following options:

    -g GLOBAL_NAME       Set the default name to replace 'print_string'
    -o HEADER_FILENAME   Set the name of the header file (default: print_string.h)
    -f FUNCTION_NAME     Set the name of the function (default: print_string)
    -v VARIABLE_NAME     Set the name of the variable (default: print_string_value)
"
    exit 1
}

# If a single argument is provided without options, use it to replace "print_string"
if [ "$#" -eq 1 ]; then
    base_name="$( echo "${1}" |sed 's/[^A-Za-z0-9][^A-Za-z0-9]*/_/g')"
    header_filename="${base_name}.h"
    function_name="${base_name}"
    variable_name="${base_name}_value"
fi

# Parse arguments
while getopts "o:g:f:v:" opt; do
    case ${opt} in
        g)  header_filename="${OPTARG}.h"
            function_name="${OPTARG}"
            variable_name="${OPTARG}_value"
            ;;
        o)  header_filename="$OPTARG"
            ;;
        f)  function_name="$OPTARG"
            ;;
        v)  variable_name="$OPTARG"
            ;;
        * ) usage
            ;;
    esac
done
shift $((OPTIND -1))


# Read the input text file or stdin
input_text=$(cat "${1:-/dev/stdin}")

# Function to escape special characters for C strings
escape_string() {
    local input="$1"
    local escaped=""
    local i
    for ((i=0; i<${#input}; i++)); do
        c="${input:i:1}"
        case "$c" in
            $'\n') escaped="${escaped}\\n" ;;
            $'\t') escaped="${escaped}\\t" ;;
            $'\r') escaped="${escaped}\\r" ;;
            '"')  escaped="${escaped}\\\"" ;;
            '\')  escaped="${escaped}\\\\" ;;
            *)
                if [[ "$c" =~ [[:print:]] ]]; then
                    escaped="${escaped}${c}"
                else
                    printf -v hex "\\x%02X" "'$c"
                    escaped="${escaped}${hex}"
                fi
                ;;
        esac
    done
    echo "$escaped"
}

# Escape the input text
escaped_text=$(escape_string "$input_text")
header_macro="$( echo "${header_filename^^}" |sed 's/[^A-Za-z0-9][^A-Za-z0-9]*/_/g')"

# Create the header file
cat > "$header_filename" <<EOF
#ifndef ${header_macro}
#define ${header_macro}

#include <stdio.h>

char ${variable_name}[] = "${escaped_text}";

void ${function_name}() {
    puts(${variable_name});
}

#endif /* ${header_macro} */
EOF

