/**
 * @file main.c
 * @author Luka Karanovic, 665778833, CSCI 360, VIU
 * @version 1.0.1
 * @date October 1, 2025
 *
 * @brief Implementation of a simple UNIX shell.
 *
 * This application implements the basic functionalities of a UNIX shell. It supports all basic UNIX 
 * commands. It supports input redirect, output redirect, and pipe commands that have exactly one 
 * command as input and one as output (no multiple piping or redirecting is supported). This shell
 * also maintains a recent command history list, which has a size defined in file 'include/360shell.h'
 * and resets to empty at the start of every session. All UNIX commands in this shell are executed 
 * within child processes created by this application.
 */


#include <stdio.h>
#include <stdlib.h>
#include "360shell.h"
#include <string.h>

int main(void) {
	
    //You can use following local variables to implement your main function.
    //You can also choose not to use these local variables and use your own set of
    //local variables instead.
    
    char command[COMMAND_MAX_LENGTH]; // memory to hold user entered command

    char* args[MAX_NUMBER_OF_ARGUMENTS + 1]; 	//memory to hold the command its arguments after parsing
    int args_length = 0;			//count of actual tokens in the argument list args[]

   
    char histories[COMMAND_HISTORY_CAPACITY][COMMAND_MAX_LENGTH];  //memory to keep track of command history 	
    int head = -1;    // refers to the oldest command in the command history
    int tail = -1;	// refers to the recent command in the command history
    
    int redirect_pos = -1;      // position of '>' or '<' or '|' character in the argument list    
    int concurrent = 0;  	// flag for concurrent processing

    while (check_exit(command, strlen(command)) != 1) {
        
        int commLen = get_command(command);
        if (commLen > 0 && commLen < COMMAND_MAX_LENGTH) {
            if (check_exit(command, strlen(command)) == 1) {
                exit(0);
            } else if (check_history(command, strlen(command)) == 1) {
                show_history(histories, head, tail);
                continue;
            } else if (check_recent(command, strlen(command)) == 1) {
                get_recent_command(histories, tail, command);
                if (strlen(command) == 0) {
                    continue;
                }
            } else {
                add_to_history(histories, &head, &tail, command);
            }

            args_length = parse_command(command, args);
            redirect_pos = check_redirect((const char**)args, args_length, ">");
            if (redirect_pos != -1) {
                handle_redirect_output(args, redirect_pos);
            } else {
                redirect_pos = check_redirect((const char**)args, args_length, "<");
                if (redirect_pos != -1) {
                    handle_redirect_input(args, redirect_pos);
                } else {
                    redirect_pos = check_redirect((const char**)args, args_length, "|");
                    if (redirect_pos != -1) {
                        handle_pipe(args, args_length, redirect_pos);
                    } else {
                        concurrent = check_concurrent((const char**)args, args_length);
                        handle_command(args, args_length, concurrent); 
                    }
                }
            } 
        }
    }

    return 0;
}

