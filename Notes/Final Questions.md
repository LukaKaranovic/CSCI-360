1. **What do you mean by independent process and cooperative process? Write about the reasons that necessitates cooperative processes and give an example application against each reason. (20 points)**  

An independent process cannot affect or be affected by any other processes.

A cooperating process can affect or be affected by other processes, including sharing data.
Reasons for cooperating processes:
- Information sharing - any multi-user application like google docs or a game
- Computation speedup - parallel sub-tasks being done - rendering videos
- Modularity - web browsers make each tab run in its own process + a UI and plugin process
- Convenience - can request to print a text document and then keep editing the text document while it is printing

2. **Explain how pipe communication works between two cooperative processes. What are the differences between named pipe and anonymous pipe? (15 points)** 

Pipe acts as a connection allowing two processes to communicate. One process writes to the pipe and another process reads from the pipe. This communication process is typically unidirectional, meaning only one side can read and one side can write.

Anonymous/ordinary pipe is unidirectional and they are limited to two processes that must have a parent-child relationship. The parent creates the pipe to communicate to a child process.

Named pipes can be accessed without a parent-child relationship as they can be accessed by name. Also unidirectional in most systems. Several processes can access this pipe by name, even at the same time.

3. **What are the advantages of using pipe communication over message queue communication? (15 points)**  

The advantages of using pipes over message queue is that pipes require less overhead as you don't need to configure any message size or priority and don't need to check if the message is full or not. Additionally, pipes are better if you need a raw data stream, as they are more responsive. You get information as the bits come in rather than having to wait for n bits to fill a message and getting them all at once.

4. **What are the advantages of shared memory communication over message queue communication? (15 points)**  

Shared memory has a higher capacity than message queue. Less load on kernel. Faster access to a lot of information.

5. **Give an example of a multi-process application that should use message queue communication and explain why message queue mechanism suits best to the application. (15 points)**  

Probably a process scheduler with a priority algorithm. Since message queue has unique trait of priorities, and CPU scheduling data is pretty consistent so can have a pre-determined best size.

6. **Write assembly codes for `mutex_lock()` and `mutex_unlock()` functions using TSL instruction so that the these functions can be used by any number of processes for mutual exclusion of critical region but without busy waiting. Explain how TSL instruction-based solution succeeds to achieve mutual exclusion and avoid busy waiting. (20 Points)**  

```assembly
	mutex_lock:
		TSL reg, mutex;
		CMP reg, #0;
		JZE ok
		CALL thread_yield
		JMP mutex_lock
	ok: RET
	
	mutex_unlock:
		MOVE mutex, #0
		RET
```
Calls thread yield which yields itself from CPU so another thread can run. When the CPU reschedules that process then it can check the lock again. Checks it every so often rather than constantly and still achieves the same goal as TSL instruction with busy waiting.

7. **Write codes for producer and consumer processes using pthread_mutex and pthread_cond. Explain, how this pthread_mutex and pthread_cond based solution avoids race condition, busy waiting, and deadlock. (25 points)**  

```c
	pthread_mutex_t mutex;
	pthread_cond_t cond_c, cond_p;
	int buffer = 0;

	void* producer(void *ptr) {
		for (int i = 1; i <= MAX; i++) {
			pthread_mutex_lock(&mutex);
			while (buffer != 0) pthread_cond_wait(&cond_p, &mutex);
			buffer = i;
			pthread_cond_signal(&cond_c);
			pthread_mutex_unlock(&mutex);
		}
		pthread_exit(0);
	}

	void* consumer (void *ptr) {
		for (int i = 1; i <= MAX; i++) {
			pthread_mutex_lock(&mutex);
			while (buffer == 0) pthread_cond_wait(&cond_c, &mutex);
			buffer = 0;
			pthread_cond_signal(&cond_p);
			pthread_mutex_unlock(&mutex);
		}
		pthread_exit(0);
	}

```
Avoids:
- Race condition: Avoids race condition with the mutex lock and `pthread_cond_wait()`
- Busy waiting: Avoids busy waiting as conditions allow process to be woken up through signal, meaning CPU can go do other tasks while condition is waiting.
	- Thread is suspended by CPU after `pthread_cond_wait()` call
- Deadlock:
	- Deadlock happens when a process/thread takes the lock and then gets suspended. But when it is suspended with `pthread_cond_wait()`, it unlocks the mutex.

8. **Write about the steps that you need to take to create and use a message queue using POSIX message queue library data structures and functions. (20 points)**  

You need to call `mq_unlink(name)` first to remove any stray message queue with the same name.

Create the `mq_attr` message queue attributes struct and add configurations to it.

Then call `mq = mq_open(<flags>, mq_attr)` with flags and attribute struct to make the message queue object mq.

Use message queue with `mq_send()` and `mq_receive()`.

Close it with `mq_close(object)` and then unlink it `mq_unlink()`
```c
	/* Remove the astray message queue with the same name */  
	mq_unlink(MQ_NAME);
	
	struct mq_attr mqattr;  
	mqattr.mq_flags = 0L;  
	mqattr.mq_maxmsg = MQ_MAX_MESSAGES;  
	mqattr.mq_msgsize = MQ_MESSAGE_SIZE;  
	mqattr.mq_curmsgs = 0L;
	
	mq = mq_open(MQ_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &mqattr);
	
	mq_close(mq);
	mq_unlink(MQ_NAME);
```

9. **Why do you need to use POSIX `ftruncate()` and `mmap()` in order to use shared memory among multiple processes. (15 points)**  

`ftruncate` - creates memory space of specified size. You need this to define how much space your shared memory will be, so you don't write or read outside of that area.
`mmap` - pointer to shared memory space. In shared memory, each process has its own virtual address range where the shared memory is located. You need `mmap()` to map these different virtual addresses to the same physical memory.

10. **Explain the usage of the following POSIX semaphore functions. (15 points)**  

a. `sem_init()` - Used to initialize a semaphore object that you are going to use in your program.  
b.`sem_destroy()` - Used to destroy a semaphore object used in your program.
c. `sem_wait()` - Used to wait for a signal that a resource is available because a process wants to use it. 
- Decrements resource counter, if counter is 0 then it waits.
d. `sem_post()` - Used to signal that a resource is available after a process is done using it. 
- Increments resource counter.

11. **If you like to solve producer and consumer problem using POSIX semaphores, how many semaphores do you need to use? Explain the usage of each semaphore in your solution. (20 points)**  

You need 3 semaphores: mutex, empty, and full.
- mutex - controls access to the critical region, is a binary semaphore
- empty - initialized to N (number of slots in buffer), counts the amount of empty buffer slots
	- producer decrements or waits on this value when it wants to produce a resource
	- consumer increments this value when it consumes a resource
- full - initialized to 0, counts the amount of full buffer slots.
	- producer increments this value when it produces a resource
	- consumer decrements or waits on this value when it wants to consume a resource

12. **What is relocation? What are the differences between static relocation and dynamic relocation? (15 points)**  

Memory relocation is where a program's virtual addresses are adjusted to match its actual physical memory addresses.

Static relocation is where the memory addresses in a process are set during compilation/load time.
- Generally, every program starts from address 0

Dynamic relocation is where the memory addresses in a process's instructions are changed during run-time. An MMU supports this. 

13. **What memory problem is being solved by swapping and how? (15 points)**  

The problem of having limited physical memory is solved by swapping. It avoids wasted memory space as processes don't need memory if they are waiting or blocked, only when they are running. When a process is waiting, it can be swapped with another process that is ready to run, then it can be swapped back when it is done waiting.

14. **If an operating system keeps track of free and allocated memory using linked list, when do the following events happen? (10 points)**  
**a. Merging of two link nodes into one.**  

This happens when a process next to a hole on one side and a process on another side terminates/frees itself. Then the process becomes a hole and merges with the adjacent hole.

**b. Merging of three link nodes into one.**

This happens when a process sandwiched between two holes gets terminated/freed.

15. **Why does operating system need to use paging? How does simple paging work? Explain with an illustration? (30 points)**  

OS needs paging to management memory efficiently. It makes address translation much easier, and reduces external fragmentation as everything is in fixed-size pages.
![[final_q15.png]]

16. **Explain first-in-first-out, second-chance, and clock page replacement algorithms. (30 points)**  

FIFO - System maintains a list of all pages currently in memory, with the most recently arrived page at the tail and least recently arrived at the head. 
- During a page fault, the page at the head is removed and the new page is added to the tail.

Second Chance - Same thing, but takes the R bit into consideration:
- R = 0:
	- Works like FIFO, page is removed and new one is added
- R = 1:
	- Page is removed from head and added to the tail, algorithm continues until it finds a page with R = 0

Clock - This algorithm works the exact same as Second Chance, but it uses a circular list instead of a doubly-linked list, meaning that you only have to maintain one pointer.
- The pointer is the "clock hand" and it advances around the list in clockwise fashion.

17. **Assume 64KB virtual address space, 16KB physical memory, and 4KB page size. The current contents of the page table of the process is shown below. The R bit in the page table shows the page reference value in the current clock tick. Translate the virtual address 37376 into the physical addresses for a read reference using WSClock page replacement algorithm. Assume current virtual time is 36228 and the clock hand is pointing to page frame 0. Draw the current, intermediate, and updated WS clocks showing the page frames and clock hand. What are the updated contents of the page table after the physical address translation is complete? (35 Points)**  
![[final_q17.png]]

Page #: 37376 // 4096 = 9
Offset: 37376 - (9 * 4096) = 512

![[final_q17_1.png]]
![[final_q17_2.png]]
![[final_q17_3.png]]
- Should be pointing up not left

18. **Why does operating system need to use segmentation? How does simple segmentation work? Explain with an illustration. (25 points)**  
OS needs to use segmentation as programs can often be too big for physical memory. We can split processes into five segments: code, data, constants, stack, and heap. 

Simple segmentation works by splitting each process into five segments so they can be allocated into memory non-contiguously.

19. **What problem is being solved using segmentation with paging and how? (20 points)**  

Sometimes segments can still be too big, and segments have to be contiguous in memory. What we can do is make a page table for each segment and page the segments, so they are still contiguous in logical addresses but then only parts of it can be accessed by physical memory as needed.

20. **Describe following structure of files: byte sequence, record sequence, and tree structure. (15 points)**  

Byte sequence: Unstructured stream of bytes. OS only sees bytes, meaning is left to user programs.

Record sequence: Sequence of fixed-length records. OS is aware of the record boundaries and structure.

Tree structure: A hierarchical organization of records. OS gives each record a "key" and sorts/searches it by the keys.

21. **Describe following file attributes: protection, owner, time of last access, time last change, current size, and maximum size. (20 points)** 

Protection: rwx bits for owner, user, group to protect unwanted users from doing unpermitted actions on file.

The owner is the person who made the file.

Time of last access is the time any memory in the file was last accessed.

Time of last change is the time any memory in the file was changed.

Current size is the size of the file in the virtual address space.

Maximum size is the maximum size this file is allowed to be.

22. **What is the benefit of keeping a pointer of a file attribute information structure inside every directory entry over keeping the file attribute information directly inside directory entry? (10 points)**  

If there are multiple copies of a file, they can share a pointer to the data structure rather than each having a copy of the attributes in each directory entry.

23. **Describe the following components of a disk layout: MBR, Partition table, Boot block, and Super block. (20 points)**

MBR - First sector on disk. It is executed when computer starts. Reads partition table and locates the activate partition and executes it.

Partition Table - Stores details about how disk is divided into partitions. Keeps track of starting addresses of all partitions and which one is active.

Boot Block - Loads OS, including filesystem, from partition into memory.

Super Block - Filesystem metadata -> filesystem type, number of blocks

24. **The following table shows which disk blocks are allocated to which files. Show MS-DOS FAT entries and directory entries related to the files and to the disk blocks. (20 points)**  
![[final_q24.png]]

No.

25. **The following table shows which disk blocks and i-nodes are allocated to which files. Show Unix i-node table entries and directory entries related to the files and to the disk blocks. (20 points)**

![[School/CSCI 360/Pasted Image Bin/final_q25.png]]

![[final_q25 1.png]]

26. **Why do Unix file systems need to use single indirect, double indirect, and triple indirect blocks in its i-node? (10 points)**  

An i-node can only store 10 disk blocks. Files can obviously be longer than 10 disk blocks, so we need a pointer to another i-node in the i-node. This nested i-node is called a single-indirect i-node. Obviously, we can have really big files that need double, triple, quadruple-indirect i-nodes.

27. **What are the differences between character devices and block devices? (10 points)**  

A character device transfers a stream of characters. No block structure and is not addressable.

A block device stores information in fixed-size blocks. It can read or write to those blocks.

28. **Describe the usages of the control register, the status register, and the data buffer of a device controller. (15 points)**  

The control register is used to send commands and config settings from the CPU to the device controller.
- "Start read", "Enable interrupt", "Set mode", etc.

The status register can be read to know the status of the device.
- Busy, error, ready, etc.

The data buffer is used to hold data in the device controller so the device can read or write to it without using the CPU.

29. **Explain the differences between memory-mapped I/O and port-mapped I/O. (10 points)**  

These are two ways to access the device controller's control registers. 

Port-mapped I/O: Accessing control registers through I/O assembly instructions and port numbers. Each register has a 8-16 bit port number.

Memory-mapped I/O: Accessing control registers through a unique memory address, where no other memory is assigned.

30. **Write both the device driver code and the interrupt handler code to print a string on a printer using interrupt driven I/O and explain how they are going to be used in the system. (15 points)**

Device driver code:
```c
	print_driver(buffer, p, count) {
		copy_from_user(buffer, p, count); // p is the kernel buffer
		i = 0; // initialize print count
		enable_interrupts();
		while(*printer_status_reg != READY); // loop until ready
		*printer_data_register = p[i++]; // output first character and
		// increment print count
		scheduler();
	}
```
Interrupt handler code:
```c
	print_interrupt_service() {
		if (count == 0) {
			unblock_user();
		} else {
			*printer_data_reg = p[i++]; // output one character and increment print count
			count--; // decrement remaining character count
		}
		acknowledge_interrupt();
		return_from_interrupt(); // IRET
	
	}
```

A user program will call a system call which will invoke the device driver code. This code initiates the job and then goes back to scheduler.

The interrupt handler code invokes after every interrupt. The interrupt handler has the responsibility of unblocking the user when done.

31. **Explain the following goals of I/O software. (30 points)**  

**a. Device independence**  
Similar methods must be used to access different types of devices of same type.
**b. Uniform naming**  
Similar naming schemes must be used for different types of devices.
**c. Error handling**  
Lower layers must handle and conceal as many errors as possible from the upper layer.
- Handle program errors, parameter errors, and I/O errors.
**d. Synchronous and asynchronous operations**  
Support synchronous/blocking or asynchronous/interrupt-driven I/O operations
**e. Buffering**  
Should employ buffers to decouple one layer from another layer.
- Can have buffer in device controller, kernel, and user space. Maybe 2 buffers in kernel

32. **Write about the functions that are performed by the device independence layer of an I/O software. (25 points)**  

System calls are performed at this layer of I/O software.

Kernel level buffering is handled here.

A lot of error reporting/handling for device specific errors are done here.

Allocating and releasing dedicated devices 
- Open and close a file
- Device queue for each device

Provides a device-independent block size.

33. **Explain the roles of interrupt hardware and interrupt handler (software) in interrupt driven I/O. Write about the functions that are performed by a typical interrupt handler. (30 points)**  

In interrupt-driven I/O, interrupt hardware/controller signals the CPU when a device needs a service. The interrupt handler (ISR) is a software routine that determines the interrupting device, what interrupt service routine to invoke, sets up the context for ISR, and copies saved registers from device driver into the process table. It then runs the ISR and when done, unblocks user and acknowledges interupt controller. Then, it gets the interrupted process to run.

34. **Explain the importance of I/O buffering in the user space, kernel space (single and double), and in the controllers. (20 points)**

We need to buffer in controllers so the device can work on its own and store the data. This is so system doesn't access device directly.

We need user space buffers so the user programs can access the data without interrupting. Also so CPU only needs to interrupt once every n characters.

We need kernel space buffer so that user space buffer can be paged out if needed. The device can keep writing to kernel space buffer and then copy it to user space buffer.

We need additional buffer in kernel space if we want the device to keep writing to buffer while it waits for CPU to acknowledge interrupt on initial buffer being full.

35. **Describe the steps that a Unix file system takes to lookup `/home/humayun/music/Blank_space.mp4` using the directory entries and i-node table entries given below. (20 points)**  
![[final_q35_1.png]]![[final_q35_2.png]]![[final_q35_3.png]]
First checks first i-node (rootdir), then goes to disk block 10.

Sees `/home` at i-node 1103. Goes to disk block 19

At disk block 19, sees `/home/humayun` is at i-node 9903. Goes to i-node table and sees that it is at disk block 89.

Goes to disk block 89, sees that `/home/humayun/music` is at i-node 2623. Then goes to disk block 65.

At disk block 65, finds blank space at i-node 2322