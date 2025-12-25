/**
 * @file tlb.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.0
 * @date May 22, 2024
 *
 * Defines the functions for translation lookaside buffer (tlb).
 *
 */




#ifndef __TLB_HEADER__
#define __TLB_HEADER__


typedef struct tlb_entry {
	int page_number;
	int frame_number;
	int valid;
} tlb_entry_t;



void init_tlb();
//Initialize tlb entries to invalid value -1
//Initialize all other variables to their appropriate initial vlaues.


void update_tlb(const int page_number, const int frame_number);
//Get the appropriate index of tlb to save the entry, call get_next_tlb_index()
//in this regard.
//Save a tlb_entry with the given page and frame numbers.



int invalidate_tlb(const int frame_number);
//Go through tlb to find out the entry which has matching 'frame_number'.
//Invalidate a tlb_entry with the given frame number, if it exists.
//Return 1, if an invalidation really happens,
//Return -1, otherwise.



int check_tlb(const int page_number);
//Go through tlb to find out the entry which has matching 'page_number'.
//Return a frame_number against the page number if such a tlb_entry exists in tlb.
//Update tlb_faults and tlb_hits appropriately.
//Return -1, otherwise.


int get_tlb_faults();
//Return tlb_fault statistics.



int get_tlb_hits();
//Return tlb_hits statistics.



int get_next_tlb_index();
//Return next tlb index that can be used to save a new tlb_entry.
//Implement FIFO replacement strategy when the tlb is full.



#endif
