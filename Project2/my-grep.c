// Parityönä tehty: Teemu Harinen ja Veeti Engblom
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

void findTerm(FILE *file, const char *searchTerm) {
  char *line = NULL;
  size_t length = 0;
  int r;

  while ((r = getline(&line, &length, file)) != -1) {
    if (strstr(line, searchTerm) != NULL) { // compare search term to line with function strstr()
      printf("%s", line);
    }
  }

  free(line);
}
int main(int argc, char* argv[])
{
	const char *searchTerm = argv[1];

	if (argc < 2) // exit if called with under two arguments
	{
		fprintf(stdout, "my-grep: searchterm [file ...]\n");
		exit(0);
	}

  if (argc == 2) {
    findTerm(stdin, searchTerm);
    exit(0);
  }

  for (int i = 2; i < argc; i++) { // loop through files and find matching term
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      fprintf(stderr, "my-grep: cannot open file '%s'\n", argv[i]);
      exit(1);
    }
    findTerm(file, searchTerm);
  }

  return (0);
}