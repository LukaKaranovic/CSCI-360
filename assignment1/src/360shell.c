/**
 * @file 360shell.c
 * @author Luka Karanovic, 665778833, Section, CSCI 360, VIU
 * @version 1.0.0
 * @date September 24, 2025
 *
 * This file contains the implementation of several staff/helper functions for the shell's functionality.
 * 
 * Functionalities include: 
 * - Checks for special commands such as 'history', 'exit', '!!'.
 * - Checks for command flags such as concurrency '&', pipe '|', input redirect '<', and output redirect '>'.
 * - Handling of normal commands, input rediect commands, output redirect commands, and pipe commands.
 * - Prompting for user command input, and the parsing of the user's command input.
 * - Managing of a recent command history circular list of size COMMAND_HISTORY_CAPACITY.
 */

#include "360shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

/** @brief Prompts the user to enter a command into the shell and stores it.
 *
 *  Prompts the user with the prmompt "CSCI360>", the user may enter any valid string 
 *  as long as its length is between 0 and COMMAND_MAX_LENGTH. If it does not satisfy the length requirements, 
 *  the buffer will wipe and the function will return -1. The string will then be stripped of the
 * '\n' newline character at the end of it and replaced with a null terminator. The command
 *  pointer will be updated in main and the command length will be returned.
 *
 *  @param command The current user command in the shell.
 *  @return The length of the user entered command, or -1 if there is an invalid command length.
 */

int get_command(char* command) {
    printf("CSCI360>");
    if (fgets(command, COMMAND_MAX_LENGTH, stdin) != NULL) {
        int commLen = strlen(command);
        if (commLen > 0 && command[commLen - 1] == '\n') {
            command[commLen - 1] = '\0';
        } else  {
            memset(command, 0, COMMAND_MAX_LENGTH);
            int c; 
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Command is too long. A command can have a maximum of %d characters.\n", COMMAND_MAX_LENGTH);
            return -1;
        }
    } 

    return strlen(command);
}

/** @brief Checks if the user entered command is "exit".
 *
 *  This function is used as a flag to know whether to run the exit command or not.
 *
 *  @param command The user entered command.
 *  @param len The length of the current user command.
 *  @return 1 if the exit command was entered, 0 otherwise.
 */

int check_exit(const char* command, const int len) {
    if (strcmp(command, "exit") == 0) {
        return 1;
    }
    return 0;
}

/** @brief Checks if the user entered command is "history".
 *
 *  This function is used as a flag to know whether to run the history command or not.
 *
 *  @param command The user entered command.
 *  @param len The length of the current user command.
 *  @return 1 if the history command was entered, 0 otherwise.
 */

int check_history(const char* command, const int len) {
    if (strcmp(command, "history") == 0) {
        return 1;
    }
    return 0;
}

/** @brief Checks if the user entered command is "!!", the 'recent command' command.
 *
 *  This function is used as a flag to know whether to run the recent command or not.
 *
 *  @param command The user entered command.
 *  @param len The length of the current user command.
 *  @return 1 if the '!!' command was entered, 0 otherwise.
 */

int check_recent(const char* command, const int len) {
    if (strcmp(command, "!!") == 0) {
        return 1;
    }
    return 0;
}

/** @brief Parses the user entered command into a list of arguments.
 *
 *  This function is used to parse the user entered command into a series of arguments.
 *  Arguments of a command are separated by the " " (space) character. This function
 *  splits the command up into arguments and adds it to an array of strings.
 *  A NULL argument is adde to the end of args to terminate the array.
 *  If a command has more than MAX_NUMBER_OF_ARGUMENTS arguments, the parsing will raise an error.
 *
 *  @param command The user entered command.
 *  @param args The parsed user command as a list of arguments.
 *  @return 1 if the command was parsed successfully, -1 if there were too many arguments.
 */

int parse_command(char* command, char* args[]) {  
    args[0] = strtok(command, " ");
    int i = 0;

    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
        // May use this for error handling later.
        if (i > MAX_NUMBER_OF_ARGUMENTS) {
            return -1;
        }
    }
    return i;
}

/** @brief Checks if the user entered command contaions the concurrency '&' flag or not.
 *
 *  The concurrency flag is meant to be used as the last argument of a command. This function checks 
 *  if the concurrency flag is the last argument of the parsed user command.
 *
 *  @param args The parsed user command as a list of arguments.
 *  @param len The number of arguments of the user command.
 *  @return 1 if the '&' flag is present, 0 if not.
 */

int check_concurrent(const char** args, const int len) {
    // Check last arg.
    if (strcmp(args[len - 1], "&") == 0) {
        return 1;
    }
    return 0;
}

/** @brief Checks if the user entered command contains the input redirect '<', output redirect '>', or pipe '|' flags.
 *
 *  Checks the entire list of arguments and flags to see if the passed command flag (as redirect) is present.
 *  In this application, this function is used to find the input redirect, output redirect, and pipe flags only.
 *
 *  @param args The parsed user command as a list of arguments.
 *  @param len The number of arguments of the user command.
 *  @param redirect The flag being searched for in the parsed command.
 *  @return The position of the flag in redirect param, if it is present. -1 if not.
 */

int check_redirect(const char** args, const int len, const char* redirect) {
    for (int i = 0; i < len; i++) {
        if (strcmp(args[i], redirect) == 0) {
            return i;
        }
    }

    return -1;
}

/** @brief Adds a user entered command to the command history array.
 *
 *  Recently executed commands are stored in a 'histories' circular list. This list has a capacity
 *  COMMAND_HISTORY_CAPACITY. The list will start empty, then the first element will be inserted at
 *  index 0. Once the list is at the history capacity, the list will remove the oldest command on the list
 *  (at head) and insert the newest command at the tail.
 *
 *  @param histories The ciruclar list holding the recent command history of the user.
 *  @param head The index of the oldest command in the histories list.
 *  @param tail The index of the most recent command in the histories list.
 *  @param command The user entered command.
 *  @return Void.
 */

void add_to_history(char histories[][COMMAND_MAX_LENGTH], int* head, int* tail, const char* command) {
    // History is empty.
    if (*head == -1 && *tail == -1) {
        *head = 0;
        *tail = 0;
        memset(histories[*tail], 0, COMMAND_MAX_LENGTH);
        strcpy(histories[*tail], command);
    } else if (*tail < COMMAND_HISTORY_CAPACITY - 1) {
        (*tail)++;
        memset(histories[*tail % COMMAND_HISTORY_CAPACITY], 0, COMMAND_MAX_LENGTH);
        strcpy(histories[*tail % COMMAND_HISTORY_CAPACITY], command);
    } else { // historyLength >= COMMAND_HISTORY_CAPACITY
        (*tail)++;
        memset(histories[*tail % COMMAND_HISTORY_CAPACITY], 0, COMMAND_MAX_LENGTH);
        strcpy(histories[*tail % COMMAND_HISTORY_CAPACITY], command);
        (*head)++;
    }
}

/** @brief Displays the users recent command history.
 *
 *  Recently executed commands are stored in a 'histories' circular list. This list has a capacity
 *  COMMAND_HISTORY_CAPACITY. Each command in this list will be displayed with a corresponding index to the user. 
 *  This display starts from the oldest command and index 0 and will go until the most recent command is reached, incrementing
 *  the index by 1 each command. If no commands were previously entered, an appropriate message will be displayed to the user.
 *
 *  @param histories The ciruclar list holding the recent command history of the user.
 *  @param head The index of the oldest command in the histories list.
 *  @param tail The index of the most recent command in the histories list.
 *  @return Void.
 */

void show_history(const char histories[][COMMAND_MAX_LENGTH], const int head, const int tail) {
    if (head == -1 && tail == -1) { 
        printf("No command history to print.\n");
        return;
    }
    int j = 0;
    for (int i = head; i <= tail; i++) {
        printf("%d \t %s \n", j, histories[i % COMMAND_HISTORY_CAPACITY]);
        j++;
    }
}

/** @brief Gets the most recent user command and makes it the current command.
 * 
 *  Recently executed commands are stored in a 'histories' circular list. The most recent
 *  command is at the tail of this list. The command is then copied to the current user command variable.
 *  If no previous commands have been entered. an appropriate message will be displayed.
 *
 *  @param histories The ciruclar list holding the recent command history of the user.
 *  @param tail The index of the most recent command in the histories list.
 *  @param command The user entered command.
 *  @return Void.
 */

void get_recent_command(const char histories[][COMMAND_MAX_LENGTH], const int tail, char* command) {
    memset(command, 0, COMMAND_MAX_LENGTH);
    if (tail != -1) {
        strcpy(command, histories[tail]);
        printf("Executing recent command: %s\n", command);
    } else {
        printf("No previous commands have been entered. Can't get recent command.\n");
    }
}

/** @brief Executes a command in a child process. Handles normal commands and concurrent ommands.
 * 
 *  The shell itself is the parent process. It will use fork() to create a child process
 *  where the passed command will execute. The parent process will wait for the child process to finish
 *  before exiting the function and prompting the next command, unless the concurrency flag is 1.
 *  If the concurrency flag is active, the parent process will not wait for the child process to finish and
 *  will take in new commands while the child process is still running.
 *
 *  @param args The parsed user command as a list of arguments.
 *  @param len The number of arguments of the user command.
 *  @param concurrent The concurrent command execution flag. 
 *  @return Void.
 */

void handle_command(char** args, int len, const int concurrent) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        fprintf(stderr, "System Error! failed to create child process.\n");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) { // For child processes
        if (concurrent == 1) {
            // Subtract length by 1 so the '&' is replaced by NULL, rather than NULL being after it.
            len--;
        }
        args[len] = NULL;

        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "An error occurred while executing the command (doesn't exist or something went wrong).\n");
        }

        exit(1);
    } else { // For parent process
        if (concurrent == 0) {
            int status;
            printf("Waiting for the child process to complete.......\n");
            waitpid(child_pid, &status, 0);
            printf(".............child completed.\n");
        } else {
            // Change later to whatever it actually is supposed to say.
            printf("Concurrent execution, not waiting for child process.\n");
        }
    }

}

/** @brief Handles the execution of a command with an output redirect (>) flag.
 * 
 *  The shell itself is the parent process. It will use fork() to create a child process
 *  where the passed command will execute. The parent process will wait for the child process to finish
 *  before exiting the function and prompting the next command. The output of the command is redirected
 *  to the file specified in the command. This is done by opening the file and redirecting STDOUT to that file.
 *  If the file to receive the output is not present, it will be created in the working directory.
 *
 *  @param args The parsed user command as a list of arguments.
 *  @param redirect_position The index location of the redirect argument in args.
 *  @return Void.
 */

void handle_redirect_output(char** args, const int redirect_position) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        fprintf(stderr, "System Error! failed to create child process.\n");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) { // For child processes
        args[redirect_position] = NULL;
        int fd = open(args[redirect_position + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

        // something is going wrong here
        if (fd == -1) {
            fprintf(stderr, "System Error! failed to create %s file.\n", args[redirect_position + 1]);
            exit(EXIT_FAILURE);
        }

        if (close(STDOUT_FILENO) == -1) {
            fprintf(stderr, "System Error!\n");
            exit(EXIT_FAILURE);
        }

        if (dup2(fd, STDOUT_FILENO) == -1) {
            fprintf(stderr, "System Error!\n");
            exit(EXIT_FAILURE);
        }

        if (close(fd) == -1) {
            fprintf(stderr, "System Error!\n");
            exit(EXIT_FAILURE);
        }
        
        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "An error occurred while executing the command (doesn't exist or something went wrong).\n");
        };
    } else { // For parent process
        printf("Waiting for the child process to complete.......\n");
        int status;
        waitpid(child_pid, &status, 0);
        printf(".............child completed.\n");
    }
}

/** @brief Handles the execution of a command with an input redirect (<) flag.
 * 
 *  The shell itself is the parent process. It will use fork() to create a child process
 *  where the passed command will execute. The parent process will wait for the child process to finish
 *  before exiting the function and prompting the next command. STDIN is redirected
 *  to the file specified in the command. This means the command's input is received from the specified file.
 *  If the input file is not present, an error will be raised.
 *
 *  @param args The parsed user command as a list of arguments.
 *  @param redirect_position The index location of the redirect argument in args.
 *  @return Void.
 */

void handle_redirect_input(char** args, const int redirect_position) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        fprintf(stderr, "System Error! failed to create child process.\n");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) { // For child processes
        args[redirect_position] = NULL;
        int fd = open(args[redirect_position + 1], O_RDONLY);

        // If opening the input file goes wrong.
        if (fd == -1) {
            fprintf(stderr, "System Error! failed to open %s file.\n", args[redirect_position + 1]);
            exit(EXIT_FAILURE);
        }

        // If closing the stdin file goes wrong.
        if (close(STDIN_FILENO) == -1) {
            fprintf(stderr, "System Error!\n");
            exit(EXIT_FAILURE);
        }

        // Copy fd to stdin file. Check if that goes wrong.
        if (dup2(fd, STDIN_FILENO) == -1) {
            fprintf(stderr, "System Error!\n");
            exit(EXIT_FAILURE);
        }

        // Check if closing input file goes wrong.
        if (close(fd) == -1) {
            fprintf(stderr, "System Error!\n");
            exit(EXIT_FAILURE);
        }


        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "An error occurred while executing the command (doesn't exist or something went wrong).\n");
        }
    } else { // For parent process
        printf("Waiting for the child process to complete.......\n");
        int status;
        waitpid(child_pid, &status, 0);
        printf(".............child completed.\n");
    }
}

/** @brief Handles the execution of a command with a pipe (|) flag.
 * 
 *  The shell itself is the parent process. It will use fork() to create two child processes
 *  that will communicate over a pipe. The pipe is opened on the write end by the first child process,
 *  meaning the command before the pipe flag will be written into the pipe. The second child process
 *  connects to the pipe on the read end, meaning the output of the first command will be used as input
 *  for the comamnd after the pipe flag. The two ends of the pipe will communicate simultaneously
 *  until the pipe has read everything (the second child process ends).
 *
 *  @param args The parsed user command as a list of arguments.
 *  @param len The length of the passed list of arguments args.
 *  @param pipe_position The index location of the pipe argument in args.
 *  @return Void.
 */

void handle_pipe(char** args, int len, const int pipe_position) {
    pid_t first_child_pid = fork();
    pid_t second_child_pid = -1;


    if (first_child_pid == -1) {
        fprintf(stderr, "System Error! failed to create child process.\n");
        exit(EXIT_FAILURE);
    } else if (first_child_pid == 0) {
        int pipe_fds[2];

        if (pipe(pipe_fds) == -1) {
            fprintf(stderr, "System Error! failed to create pipe.\n");
            exit(EXIT_FAILURE);
        }
        
        pid_t second_child_pid = fork();
        // Execute second command with first as input.
        if (second_child_pid == -1) {
            fprintf(stderr, "System Error! failed to create child process.\n");
            exit(EXIT_FAILURE);
        } else if (second_child_pid == 0) {
            // Update the variable to be actual process ID, not what fork() returns.
            second_child_pid = getpid();
            close(pipe_fds[WRITE_END]);
            close(STDIN_FILENO);
            dup2(pipe_fds[READ_END], STDIN_FILENO);
            args[len] = NULL;
            if (execvp(args[pipe_position + 1], &args[pipe_position + 1]) == -1) {
                fprintf(stderr, "An error occurred while executing the command (doesn't exist or something went wrong).\n");
            }
        } 

        close(pipe_fds[READ_END]);

        close(STDOUT_FILENO);
        dup2(pipe_fds[WRITE_END], STDOUT_FILENO);
        args[pipe_position] = NULL;
        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "An error occurred while executing the command (doesn't exist or something went wrong).\n");
        }

    } else {
        printf("Waiting for the child process to complete.......\n");
        int status;
        waitpid(second_child_pid, &status, 0);
        printf(".............child completed.\n");
    }
}
