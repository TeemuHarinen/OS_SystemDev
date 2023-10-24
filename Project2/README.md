# Project 2 - Unix Utilities
## Project 2/3 of "Käyttöjärjestelmät ja systeemiohjelmointi" practical assignment

To use the program, use commands below:

### my-cat

$ ./my-cat [file] - reads the file and outputs to console

$ ./my-cat [inputfile] [outputfile] - reads the inputfile and writes contents to outputfile

### my-grep

$ ./my-grep examplestring [file1] [file2] [file...] - finds given string from file(s)

### my-zip

$ ./my-zip file1 [file2] ... - my-zip compresses the file using repeating characters. Example of the compression: "aaaabb" --> "4a2b" 

### my-unzip

$ ./my-unzip file1 [file2] ... - my-unzip decompresses a file by reversing what my-zip did. Example of the decompression: "4a2b" --> "aaaabb" 
