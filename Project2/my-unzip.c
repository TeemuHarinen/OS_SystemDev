#include <stdio.h>
#include <stdlib.h>

void unzip(FILE *inputFile) {
    int counter;;
    int currChr;

    while (fread(&counter, sizeof(int), 1, inputFile) == 1) {
        currChr = fgetc(inputFile);

        // repeat character count
        for (int i = 0; i < counter; i++) {
            putchar(currChr);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // If no file specified, exit with status 1
        fprintf(stderr, "my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "my-unzip: cannot open file '%s'\n", argv[i]);
            exit(1);
        }

        unzip(file);
        fclose(file);
    }

    return (0);
}