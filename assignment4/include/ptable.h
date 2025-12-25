/**
 * @file ptable.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.0
 * @date May 22, 2024
 *
 * Defines the functions for page table.
 *
 */



#ifndef __PTABLE_HEADER__
#define __PTABLE_HEADER__


void init_ptable();
//Initialize page table entries to invalid value -1
//Initialze all other variables to their appropriate initial values.


void update_ptable(const int page_number, const int frame_number);
//Set the frame_number value at page number index of page table.



int invalidate_ptable(const int frame_number);
//Go through the page table to find out the entry which has matching 'frame_number'
//Invalidate the page table entry if it contains the frame number by setting it to -1.
//Return 1 if invalidation happens, -1 otherwise.



int check_ptable(const int page_number);
//Return the frame number against the page number, if it is not a page fault.
//Update page fault and page hit statistcs appropriately.



int get_page_faults();
//Return page fault statistics.



int get_page_hits();
//Return page hit statistics.



int get_next_frame_number();
//Determine a frame number which is either an empty frame or an appropriate frame following FIFO page
//replacement strategy.
//Call invalidate_ptable() to invalidate the page table entry associated with the frame number.
//Call invalidate_tlb() from 'tlb.h' to invalidate the tlb entry associated with the frame number.
//Return the frame number.


#endif
