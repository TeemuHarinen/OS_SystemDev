#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64
#define PATH_MAX 64

char* search_path[PATH_MAX];
char* original_path[PATH_MAX];

// function for printing error messages
void print_error() {
  char error_message[30] = "An error has occurred\n";
  write(STDERR_FILENO, error_message, strlen(error_message));
}

// function to handle parsing arguments
void parse_input(char *input, char *args[]) {
    char *token = strtok(input, " \t\n");
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

// function to execute user commands
void execute_command(char *args[]) {
    pid_t pid = fork(); // create a new child process

    if (pid == 0) {
      
        execvp(args[0], args); // replace the process with args from user/file
        // if execvp fails, returns here
        print_error();
        exit(1);
    } else if (pid > 0) {
        // wait for child process to complete
        int status;
        wait(&status);
    } else {
        print_error();
    }
}

// function to set search path for external commands
void set_path(char *args[]) {
    int i = 1;
    while (args[i] != NULL) {
        search_path[i - 1] = args[i];
        i++;
    }
    search_path[i - 1] = NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 1 && argc != 2) {
        fprintf(stderr, "Usage: %s [batch_file]\n", argv[0]);
        exit(1);
    }

    // control whether to use interactive or file mode
    int interactive = (argc == 1);

    FILE *input_file = stdin;
    if (!interactive) {
        input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            print_error();
            exit(1);
        }
    }

    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    int checkPath = 0;
    search_path[0] = "/bin"; // Default search path
    // Copy the default search path to the original_path array
    for (int i = 0; search_path[i] != NULL; i++) {
        original_path[i] = strdup(search_path[i]);
    }
    original_path[PATH_MAX - 1] = NULL;

    // interactive program loop
    while (1) {
        if (interactive) {
            printf("wish> ");
        }

        if (fgets(input, sizeof(input), input_file) == NULL) {
            if (!interactive) {
                fclose(input_file);
            }
            exit(0);
        }

        parse_input(input, args);

        if (args[0] == NULL) { // empty line
            continue;
        }

        if (strcmp(args[0], "exit") == 0) { // exit program
            exit(0);
        } else if (strcmp(args[0], "cd") == 0) { // change directory
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else if (chdir(args[1]) != 0) {
                print_error();
            }
        } else if (strcmp(args[0], "path") == 0) {
            set_path(args);
        } else {
            // Check each directory in the search path
            int i = 0;
            while (search_path[i] != NULL) {
                char command_path[PATH_MAX];
                snprintf(command_path, PATH_MAX, "%s/%s", search_path[i], args[0]);
                if (access(command_path, X_OK) == 0) {
                    // Command found in the current directory in the search path
                    execute_command(args);
                    checkPath = 1;
                    break;
                } 
                i++;
            }
            if (checkPath == 0) {
                printf("command not regognized\n");
            }
            checkPath = 0;

            // Restore the original search path
            for (int j = 0; original_path[j] != NULL; j++) {
                search_path[j] = strdup(original_path[j]);
            }
            search_path[PATH_MAX - 1] = NULL;
        }

    }

    return 0;
}
