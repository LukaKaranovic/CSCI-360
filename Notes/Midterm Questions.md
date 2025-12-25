1. What are the main roles of operating systems? How do operating systems play these roles? (15 points)

Operating systems have 2 main roles:
i. Extending the Machine: OSs provide a layer of abstraction over low-level operations and hardware to make the interface nicer (less ugly)
ii. Managing Resources: OSs manage numerous hardware resources so that they are all being used efficiently and effectively.
- Does this through time and space multiplexing
- Manages through memory allocation, CPU scheduling, file systems, etc.

2. What do you mean by time and space multiplexing? What kind of resources are time multiplexed? What kind of resources are space multiplexed? (15 points)

Time multiplexing is multiple things sharing a resource among time slices, meaning one thing gets to access a resource at a time.
- CPU execution/burst time is time multiplexed - one process gets to be executed by the CPU at a time
Space multiplexing is multiple things sharing a resource among space allocation, meaning that all of the things get a limited amount of that resource at the same time
- Memory management is space multiplexed - each process gets a portion of the computer's memory for itself

3. What do you mean by user and kernel modes? Why do operating systems need these modes? (15 points)
User mode: This is the mode where all user applications and programs run, it does not have access to the hardware or any privileged instructions.
Kernel mode: This is the mode the kernel (core part of OS) runs in. It has direct access to hardware and can carry out privileged instructions.

It provides a layer of security within the system:
- Otherwise, viruses or buggy programs would be able to access hardware automatically and do many harmful things to your system.
It also provides stability, as crashes are localized:
- A user program crashing will only crash its environment, not the entire system.
It makes managing resources easier:
- Kernel controls and handles all resource management, meaning user programs can't accidentally misuse a shared resource.

4. How does the operating system switch from user mode to kernel mode and switch back from kernel mode to user mode? (15 points)
The OS switches from user mode to kernel mode through a trap or interrupt, which causes the hardware to switch its mode bit from 1 to 0.

The IRET (return from interrupt) operation is used to return back to user mode, it causes the hardware to switch the mode bit from 0 to 1.

5. Show the control flows and both the user space and kernel space routines involved in write(fd, &buffer, size) system call. (25 points)
- Application program calls `write(fd, &buffer, size)`
- Invokes User Space System Call Routine, which calls a trap
- Trap calls the Kernel Space Trap Handler
- Kernel Space Trap Handler calls the Kernel Space Syscall Routine (Dispatcher)
- Dispatcher calls the Write Kernel Space Routine (system call)
- When the Write Routine finishes, returns to dispatcher
- Dispatcher returns to Kernel Space Trap Handler
- Kernel Space Trap Handler calls IRET (return from interrupt) which goes to hardware and flips mode bit back to user mode. This returns to the User Space System Call Routine
- User Space System Call Routine returns to application program

6. List all the user space and kernel space routines involved in write(fd, &buffer, size) system call and explain their roles. (25 points)
Application program - calls `write(fd, &buffer, size)` system call and stores the parameters to registers
User Space System Call Routine - Gets syscall # for `write()` and stores it in a register, calls trap
Kernel Space Trap Handler - Recognizes it is a syscall trap and calls the Kernel Space Syscall Routine (Dispatcher)
Kernel Space Syscall Routine (Dispatcher) - Takes syscall # from register and finds appropriate system call routine to invoke
Write Kernel Space Routine - Pulls the parameters from registers and does the write operation on file

7. What are the advantages and disadvantages of a microkernel architecture operating system over a monolithic architecture operating system? (10 Points)

Advantages:
- Security - Harder to be breached as less things have access to hardware. Also one service being compromised doesn't necessarily give full control of the OS
- Fault Isolation - Since the OS is split up into parts, can figure out more precisely what area of OS is causing faults, with monolithic there isn't a way to isolate faults
- Maintenance - Easier to upgrade microkernel because you don't have to recompile everything at once
Disadvantages
- Speed - Monolithic is faster because everything is in one file (less context switching and IPC)
- Cost - Microkernel architecture is typically more complex and costs more to develop. Monolithic is simple and cheaper.

8. What is a process? Explain different ways to create and to terminate a process. (15 points)
A process is a program in execution.
Creation:
i. User request to create a new process
ii. Initiation of a batch job
iii. Created by another process (`fork()`)
iv. System initialization

Deletion:
Voluntary:
i. Normal exit - process terminates with no errors (`return 0` or `exit(0)`)
ii. Error exit - process terminates on its own with an error (return non-zero code)
Involuntary:
i. Killed by another process - parent process uses `kill` operation on it
ii. Fatal error - process does something bad and the OS kills it

9. Determine whether the following state transition of a process is valid or invalid and explain the reason: (15 points)
a. Ready – Running
- Valid - process is in ready queue and CPU scheduler picks it to be executed next
b. Running – Blocked
- Valid - process is being run by CPU and then it requires I/O, so the CPU blocks it until I/O happens and the process is ready again
c. Blocked – Running.
- Invalid - A process has to be ready before it can be executed by the CPU, otherwise, CPU has no knowledge of the process being ready and cannot choose to give it burst time.

10. Draw the memory footprint of a process and explain its different section. (15 points)
From address 0:
Text - The actual code/text of the program
Data - global variables and constants
Heap - Holds dynamically allocated variables (runtime)
(Unallocated Space)
Stack - Holds function calls, local variables, etc.

11. What is the process control block and what information are kept in process control block? (15 points)
A PCB is a data structure that holds metadata about a process, there is one PCB entry for each current process.
- Process Information:
	- Process IDs, state, program counter, CPU register values, CPU scheduling algorithm information, accounting information
- Memory Management Info:
	- Pointers to text, data, heap, and stack segments - info of how much space each segment takes up
- File Management Info
	- Root and working directories
	- List of files the process has opened
	- User and group IDs of those files/directories

12. What are the advantages and disadvantages of a multi-threaded application over a multi-process application? (15 points)
Advantages:
- Can run different parts of the application concurrently as opposed to serially
- No IPC and less context switching (less dispatch latency) as data is shared within the same memory space
Disadvantages:
- Possibility of race conditions or deadlocks as multiple threads can access the same memory at the same time.

13. In which state and queue a process should be in its I/O burst? Explain your answer. (10 points)
The process will be in a Blocked state during it's I/O burst. This is so it cannot be scheduled by the CPU while it is waiting for I/O because that would be a waste of the CPU's time.
It will likely be in an I/O device waiting queue, waiting for I/O from a specific device.

14. What is the purpose of a ready queue? What are the possible events that put a process into the ready queue? What are the possible events that put a process out of the ready queue? (15 points)
The purpose of a ready queue is to tell the scheduler what processes are ready to be picked by the CPU to be executed so it can schedule them.
- A process can be put into the ready queue when it has returned from an I/O burst (interrupt tells OS about it)
- A process can also be put into the ready queue if it has just started
- In pre-emptive scheduling algorithms, a process may be put into the ready queue if it was pre-emptively kicked out of the 'Running' state

- A process can be taken out of the ready queue by being selected by the CPU scheduler to be run next, its state will be changed to 'Running'
- A process can also be taken out of the ready queue if it is killed by the OS or another process.

15. What do you mean by pre-emptive scheduling? List and explain the situations at which pre-emptive scheduling decisions take place. (10 points)
Pre-emptive scheduling algorithms are algorithms that may stop a process before it finishes its job by interrupting the CPU and switching it to another process. The process may be kicked out through an interrupt or upon expiration of its time slice.

16. What is context switching? How does it affect dispatch latency? (10 points)
Context switching happens when the CPU switches processes. It stores the current process's data into its PCB object and then loads the new process's data from its PCB into memory. This is so the CPU can start executing the process from where it left off, rather than restarting from the top of the program every time.

The more complex context switching is, the higher the dispatch latency. This is because the dispatcher will have to go through more operations to context switch.

17. Explain Lottery scheduling algorithm. (10 points)
The lottery scheduling algorithm runs a lottery n times per second to decide which process gets a CPU time slice of 1/n seconds. 

The scheduler gives out tickets to every process and it selects one of the tickets at random, whatever process has that ticket gets the CPU burst.
- Higher priority processes can be given additional tickets

18. Explain the usage of dup2() system call. (10 points)
The dup2() system call is used to duplicate a file descriptor. It is commonly used for redirection of stdin, stdout, or stderr streams (generally to a file).

19. Explain the usage of the pthread_create() function from the pthread library. (10 points)
`pthread_create()` is used to create a new thread in a process. It is passed 4 parameters:
i. The address of the pthread object
ii. Any attributes of the thread
iii. The routine the thread will execute
iv. Any arguments passed to the thread

20. Guess the next CPU burst, if a process had followed previous CPU bursts in milliseconds. Assume 10 millisecond as your first guessed CPU burst and x = 0.5. (15 points)
	19, 11, 13, 3, 17, 13, 7, 9, 13, 18, 14, 16, 19

atn + (1-a)Tn = Tn+1

With a = 0.5:
0.5tn + 0.5Tn = Tn+1

0.5 * 19 + 0.5 * 10 = 14.5
0.5 * 11 + 0.5 * 14.5 = 12.75
0.5 * 13 + 0.5 * 12.75 = 12.875
0.5 * 3 + 0.5 * 12.875 = 7.9375
0.5 * 17 + 0.5 * 7.9375 = 12.46875
0.5 * 13 + 0.5 * 12.46875 = 12.734375
0.5 * 7 + 0.5 * 12.734375 = 9.8671875
0.5 * 9 + 0.5 * 9.8671875 = 9.43359375
0.5 * 13 + 0.5 * 9.43359375 = 11.216796875
0.5 * 18 + 0.5 * 11.216796875 = 14.6083984375
0.5 * 14 + 0.5 * 14.6083984375 = 14.3041992188
0.5 * 16 + 0.5 * 14.3041992188 = 15.1520996094
0.5 * 19 + 0.5 * 15.1520996094 = 17.0760498047

21. Draw Gantt chart and compute average response time and average turnaround time for following processes using Priority with Round Robin scheduling algorithm. Assume the higher the number: the higher the priority and a quanta of 5 CPU burst. (20 points)

| Process | Arrival Time | CPU Bursts | Priority |
| ------- | ------------ | ---------- | -------- |
| P1      | 0            | 40         | 3        |
| P2      | 4            | 55         | 9        |
| P3      | 3            | 30         | 3        |
| P4      | 7            | 20         | 4        |
| P5      | 2            | 50         | 3        |
| P6      | 5            | 35         | 7        |

P1 -> 

P2 -> P2 -> P2 -> P2 -> P2 -> P2 -> P2 -> P2 -> P2 -> P2 -> P2 -> 

P6 -> P6 -> P6 -> P6 -> P6 -> P6 -> P6 ->

P4 -> P4 -> P4 -> P4 -> 

P1 -> P5 -> P3 ->
P1 -> P5 -> P3 ->
P1 -> P5 -> P3 ->
P1 -> P5 -> P3 ->
P1 -> P5 -> P3 ->
P1 -> P5 -> P3 ->
P1 -> P5 ->
P5 ->
P5 ->
P5 ->

| Process | Response Time | Turnaround Time |
| ------- | ------------- | --------------- |
| P1      | 0             | 210-0 = 210     |
| P2      | 5-4 = 1       | 60-4 = 56       |
| P3      | 125-3 = 122   | 205-3 = 202     |
| P4      | 95-7 = 88     | 115-7 = 108     |
| P5      | 120-2 = 118   | 230-2 = 228     |
| P6      | 60-5 = 66     | 95-5 = 90       |
| Average | 65.83         | 149             |

22. Write a function to execute a Linux command in a child process and redirect its output to a file. Assume your function will receive the command and its argument as `char* args[]`. (20 points)  

```c
	void output_redirect(char* args[]) {
		pid_t child_pid = fork();
	
		if (child_pid == 0) {
			close(stdout_fileno);
			dup2(output_file, stdout_fileno);
			close(output_file);
			execvp(args[0], args);
		
		} else {
			waitpid(child_pid);
		}	
	}
```

23. Write code for a multithreaded application that will find the minimum from an MxN matrix, represented by a two-dimensional array of integers, creating M threads, passing the row number as the thread function parameter, and giving the responsibility to each thread function to find the minimum in a single row and to write that minimum into another array of integers of size M at appropriate index. You will need to use `pthread_create()`, `pthread_exit()`, and `pthread_join()` functions from pthread library. (30 points)

```c
	void* minimumInRow(void* param) {
		int row = *(int*)param;
		
		int* min = (int*)malloc(sizeof(int));
		*min = matrix[row][0];
		for (int i = 1; i < N; i++) {
			if (matrix[row][i] < *min) {
				*min = matrix[row][i];
			}
			
		}
		
		free(param);
		
		pthread_exit(min);
	}
	
	int findMinInMatrix(int M, int N, int matrix[M][N]) {
		int* minimums[M];
		pthread_t thread_array[M];
		for (int i = 0; i < M; i++) {
			int* a = malloc(sizeof(int));
			*a = i;
			pthread_create(&thread_array[i], NULL, minimumInRow, a);
		}
		for (int i = 0; i < M; i++) {
			pthread_join(thread_array[i], (void**) &minimums[i]);
		}
		int min = *minimums[0];
		for (int i = 1; i < M; i++) {
			if (*minimums[i] < min) {
				min = *minimums[i];
			}
			free(minimums[i]);
		}
		
		return min;
	}
	
	int M, N;
	int matrix[M][N];
	
	int main() {
		findMinInMatrix(matrix, M, N);
		return 0;
	}
```