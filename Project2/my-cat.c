// Parityönä tehty: Teemu Harinen ja Veeti Engblom
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

int main(int argc, char* argv[])
{
	FILE* file;
	char chr;
	int a;
	char filename[MAX];

	if (argc == 1) // exit when called without arguments
	{
		fprintf(stdout, "No files specified, exiting program\n\n");
		exit(0);
	}
	
	for (a = 1; a < argc; a++) // loops through all the files
	{
		strcpy(filename, argv[a]);
		file = fopen(argv[a], "r");

		if (file == NULL) // exit when file is not found
		{
			fprintf(stdout, "my-cat: cannot open file '%s'\n", filename);
			exit(1);
		}

		fprintf(stdout, "printing out the contents of the file '%s': \n\n", filename);
		while((chr = getc(file)) != EOF) // read file one character at a time until EOF
		{
			printf("%c", chr);
		}
		
		fclose(file);
		fprintf(stdout, "\n EOF for file '%s'\n\n", filename);
	}

	return 0;
}
