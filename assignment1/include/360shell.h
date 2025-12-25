/**
 * @file 360shell.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version  1.0.1
 * @date May 20, 2024
 *
 * Defines the macros (constants) and the functions required for simple shell application.
 *
 */


#ifndef __360_SHELL_HEADER__
#define __360_SHELL_HEADER__


#define COMMAND_MAX_LENGTH 80 			/* Maximum 80 chars per command */
#define MAX_NUMBER_OF_ARGUMENTS 40		/* Maximum 40 arguments for a command */
#define COMMAND_HISTORY_CAPACITY 10		/* Maximum 10 command histories */
#define EXIT_COMMAND_LENGTH 4			/* Length of 'exit' command */
#define HISTORY_COMMAND_LENGTH 7		/* Length of 'history' command */
#define RECENT_COMMAND_LENGTH 2			/* Length of '!!' command */
#define READ_END    0				/* Read end of pipe file descriptor pair */
#define WRITE_END   1				/* Write end of pipe file decriptor pair */



int get_command(char* command); 
//Display 'CSCI360>' prompt to the user.
//Accept a command from the user through standard input (keyboard) and put it into 'command' parameter
//Trim the new line character from the end of user entered command
//Return the length of the command after trimming the new line character.
//You can use C functions printf(), fflush(), memset(), fgets(), strchr(), and strlen().


int check_exit(const char* command, const int len);
//Return 1, if the command is 'exit' command, 0 otherwise.
//You can use C function strcmp().


int check_history(const char* command, const int len);
//Return 1, if the command is 'history' command, 0 otherwise.
//You can use C function strcmp().


int check_recent(const char* command, const int len);
//Return 1, if the command is recent '!!', 0 otherwise.


int parse_command(char* command, char* args[]);
//Extract command and its arguments into the list of arguments 'args'.
//The command and its arguments are space separated.
//You can use strtok() standard library function to separate individual tokens from 'command'.
//Put the command, e.g., 'ls' from 'ls -la src' command, at args[0], 
//the first argument, e.g., '-la', at args[1], and the second argument 'src' at args[2].
//Count the number of tokens and return your count. For above example 'count' is 3.
//Your count should be less than or equal to MAX_NUMBER_OF_ARGUMENTS. 


int check_concurrent(const char** args, const int len);
//Check whether concurrent execution of the processes has been requested by giving an "&"
//as the last argument of the command or not.
//Return 1, if so, 0 otherwise.
//You can use C function strcmp().


int check_redirect(const char** args, const int len, const char* redirect);
//Check whether the 'redirect' character is present in the argument list 'args' or not.
//In this assignment, you can assume single occurance of redirect character in your user commands.
//Return the position of the redirect character in the list if present, return -1 otherwise.
//You can use C function strcmp().


void add_to_history(char histories[][COMMAND_MAX_LENGTH], int* head, int* tail, const char* command);
//Use 'histories', an array of strings, as a circular list to add the command into it.
//The command at index 'head' should refer to the oldest command in the history and 
//and the command at index 'tail' should refer to the newest command in the history.
//The length of each command in history must be less than or equal to COMMAND_MAX_LENGTH.
//The capacity of command history is equal to COMMAND_HISTORY_CAPACITY.   
//Add the 'command' at the appropriate position in the 'histories' and update the 'head' 
//and 'tail' indexes appropriately.
//You can use C functions memset() and strcpy().


void show_history(const char histories[][COMMAND_MAX_LENGTH], const int head, const int tail);
//Loop through all the recent histories in order, starting from the 'head' and ending at 'tail'.
//Display them in separate lines with the order number.
//Display the order numbers in the first column and the command in the second column in
//each line.
//You can use C function printf().


void get_recent_command(const char histories[][COMMAND_MAX_LENGTH], const int tail, char* command);
//Copy the most recent command from the command histories into 'command' parameter.
//You can use C functions memset() and strcpy().


void handle_command(char** args, int len, const int concurrent);
//Create a child process using fork() system call to execute the command in a child process.
//Inside the child process, add a NULL argument after the last argument in argument list 'args'.
//If concurrent character is present, which is usually the last argument in the list, replace it
//with a NULL argument.
//Assume no other special argument, e.g., input redirect, output redirect, and pipe, is present if 
//concurrent argument is present in the command.
//Replace the child process image with the image specified by 'args[0]' using execvp() system call.
//System call execvp() will execute the command with its arguments.
//Inside the parent process, wait for the child process to complete if concurrent processing is not
//requested using waitpid() system call. Do not wait, otherwise.
//Inform the user appropriately.


void handle_redirect_output(char** args, const int redirect_position);
//Create a child process using fork() system call to execute the command in a child process.
//Inside the child process, add a NULL argument at redirect position in argument list 'args'.
//Assume no other special argument, e.g., input redirect, pipe, and concurrent, is present if 
//output redirect argument is present in the command.
//Assume only one output redirect argument is present in the command at 'redirect_position'. 
//Open a file descriptor using open() system call in write only mode. Use the string after
//the redirect position in argument list as the output file name in your open() system call.
//Redirect the standard output by copying the opened file descriptor into the standard output file 
//descriptor (STDOUT_FILENO) using dup2() system call.
//Close the opened file descriptor using close() system, since you don't need it anymore.
//Replace the child process image with the image specified by 'args[0]' using execvp() system call.
//System call execvp() will execute the command with its arguments and the output of the executed
//command will be saved into the redirected file.
//In the parent process, wait for the child process to complete using waitpid() system call. 
//Inform the user appropriately.



void handle_redirect_input(char** args, const int redirect_position);
//Create a child process using fork() system call to execute the command in a child process.
//Inside the child process, add a NULL argument at redirect position in argument list 'args'.
//Assume no other special argument, e.g., output redirect, pipe, and concurrent, is present if 
//input redirect argument is present in the command.
//Assume only one input redirect argument is present in the command at 'redirect_position'. 
//Open a file descriptor using open() system call in read only mode. Use the string after
//the redirect_position in argument list as the input file name in your open() system call.
//Redirect the standard input by copying the opened file descriptor into the standard input file 
//descriptor (STDIN_FILENO) using dup2() system call.
//Close the opened file descriptor using close() system, since you don't need it anymore.
//Replace the child process image with the image specified by 'args[0]' using execvp() system call.
//System call execvp() will execute the command with its arguments and read the input for the 
//executed command from the redirected file.
//In the parent process, wait for the child process to complete using waitpid() system call.
//Inform the user appropriately.




void handle_pipe(char** args, int len, const int pipe_position);
//Create the first child process using fork() system call to execute the first command in a child process.
//Assume no other special argument, e.g., output redirect, input redirect, and concurrent, is present if 
//pipe argument is present in the command.
//Assume only one pipe argument is present in the command at 'redirect_position'. 
//Inside the first child process, use pipe() system call to open a pipe with two file descriptors, 
//one for reading and the other for writing, and create the second child process using fork() system call again. 
//You will be using your first child process to execute the user command that has been passed 
//before the pipe and to write its output into your pipe.
//You will be using your second child process to execute the user command that has been passed after
//the pipe and to read its input from the pipe.
//Inside the second child process, close the write file descriptor of the pipe and the standard input file 
//descriptor (STDIN_FILENO) using close() system call, redirect its input by copying the read 
//file descriptor of the pipe into its standard input file descriptor (STDIN_FILENO) using dup2() system call,
//end the argument list 'args' of the command with a NULL argument, replace the process image with the 
//image specified by the command after the pipe_position using execvp() system call.
//Continue coding inside the first child process, close the read file descriptor of the pipe and the
//standard ouput file descriptor (STDOUT_FILENO) using close() system call, redirect its
//output by copying the write descriptor of the pipe to the standard output file descriptor (STDOUT_FILENO)
//using dup2() system call, end the argument list 'args' of the command before the pipe by inserting
//NULL argument at pipe_position, replace the process image with the image specified by the command before 
//the pipe using excvp() system call.
//In the parent process, wait for the second child processes to complete using waitpid() system call.


#endif
