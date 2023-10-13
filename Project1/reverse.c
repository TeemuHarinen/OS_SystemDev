// Parityönä tehty: Teemu Harinen ja Veeti Engblom
// Lähteet:
//https://www.geeksforgeeks.org/c-program-to-reverse-the-content-of-the-file-and-print-it/
//https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to reverse input file contents and output to a file
void reverse(FILE *input, FILE *output) {
    char **lines = NULL;
    size_t line_count = 0;
    char *line = NULL;
    ssize_t read;
    int counter = 0;
    // Read lines into an array of strings
    while ((read = getline(&line, &line_count, input)) != -1) {
        lines = (char **)realloc(lines, (line_count + 1) * sizeof(char *));
        if (lines == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        lines[counter] = strdup(line);
        line_count++;
        counter++;
    }
    free(line);

    // Print lines in reverse order
    for (ssize_t i = counter - 1; i >= 0; i--) {
        fprintf(output, "%s", lines[i]);
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;

    // Handle command-line arguments
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    } else if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        if (argc == 3) {
          // Check if input and output files are the same
          if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
             }
            output = fopen(argv[2], "w");
            if (output == NULL) {
                fclose(input);
                fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
                exit(1);
            }
        }
    }
    
    reverse(input, output);

    // Close files if not stdin or stdout
    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }

    return 0;
}
