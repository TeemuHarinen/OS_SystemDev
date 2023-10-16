// Parityönä tehty: Teemu Harinen ja Veeti Engblom
#include <stdio.h>
#include <stdlib.h>

void zip(FILE *inputFile) {
  int prevChr = EOF;
  int counter = 0;
  int currChr;

  while((currChr = fgetc(inputFile)) != EOF) {
    if (currChr == prevChr) { // if current character is the same as previous, increment counter
      counter++;
    } else {

      if (prevChr != EOF) {
        fwrite(&counter, sizeof(int), 1, stdout); // write 
        putchar(prevChr);
      }
      counter = 1;
      prevChr = currChr;
    }

  }
  // write last character and its count
  if (prevChr != EOF) {
    fwrite(&counter, sizeof(int), 1, stdout);
    putchar(prevChr);
  }
}

int main(int argc, char *argv[]) {
    if (argc < 2) { // if no file is specified, exit program
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "my-zip: cannot open file '%s'\n", argv[i]);
            exit(1);
        }

        zip(file);
        fclose(file);
    }

    return (0);
}