/**
 * @file config.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.0
 * @date May 22, 2025
 *
 * Defines macros rekated to virtual memory management system.
 *
 */


#ifndef __CONFIG__HEADER__
#define __CONFIG_HEADER__

#define FRAME_SIZE 256			//The size of each frame in the physical memory
#define NUMBER_OF_FRAMES 64		//The total number of frames available in the physical memory

#define PAGE_SIZE 256			//The size of each page in the virtual memory
#define NUMBER_OF_PAGES 256		//The total number of pages in the virtual memory

#define NUMBER_OF_TLB_ENTRIES 16	//The total number of TLB entries.

#endif
