/**
 * @file pmemory.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.1
 * @date May 22, 2024
 *
 * Defines the functions for physical memory.
 *
 */



#ifndef __PMEMORY_HEADER__
#define __PMEMORY_HEADER__

#include <stdio.h>


signed char get_value(const int frame_number, const int offset);
//Return the value of the byte that is addressed by the frame number and the offset at
//the physical memory.



int load_page(const int page_number, FILE* bkstr);
//Locate the page referred by the page number from the backing store by calling fseek() library function.
//Read the page into a temporary buffer by calling fread() library function.
//Find a frame number calling get_next_frame_number() from 'ptable.h', where this page will be loaded.
//Function get_next_frame_number() returns a frame number that is either empty  or 
//being replaced using appropriate page replacement strategy.
//Page replacement is decided by page table module'ptable.h' since it holds all page related statistics.
//However, actual loading of the page from the backing store to the physical memory is performed here
//in physical memory module.
//Copy the content of the temporary buffer (page) into the selected frame by calling memcpy() library function.
//Update the page number and the associated frame number at tlb by calling update_tlb() from 'tlb.h'
//Update the page number and the associated frame number at page table by calling update_ptable()
//from 'ptable.h'.
//Return the physical frame number where the page has been loaded.


#endif
