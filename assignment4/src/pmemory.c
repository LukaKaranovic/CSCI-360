/**
 * @file pmemory.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date November 19, 2025
 *
 * Implements the physical memory component of this memory management application.
 * Instantiates the physical memory as a signed character array. Has functions to load a page from
 * virtual memory into physical memory and to get the value from a specific physical memory address.
 */

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "ptable.h"
#include "tlb.h"

signed char phys_mem[NUMBER_OF_FRAMES * (FRAME_SIZE * sizeof(signed char))];        // Physical memory implementation as a signed char array.


/** @brief Goes to a physical memory address and returns an 8-bit integer as a signed char.
 *
 *  @param frame_number The frame number of the physical memory address.
 *  @param offset The offset number of the physical memory address.
 *  @return The signed character byte (8-bit integer) at the physical memory address.
 */

signed char get_value(const int frame_number, const int offset) {
    return phys_mem[(frame_number * FRAME_SIZE) + offset];
}

/** @brief Loads a page from virtual memory into a physical page frame.
 *
 *  This function is called if there is no TLB entry and no page table entry for this page. It loads
 *  the page from the backing store file (bkstr) and reads in a FRAME_SIZE amount of bytes to a buffer, which
 *  is copied into physical memory. 
 *
 *  Both the TLB and page table are updated with the new page entry.
 *
 *  @param page_number The number of the page in virtual memory to be loaded into physical memory.
 *  @param bkstr The backing store file, where all of the pages are kept.
 *  @return The frame number that the page was loaded in to.
 */ 

int load_page(const int page_number, FILE* bkstr) {
    signed char buffer[PAGE_SIZE];
    fseek(bkstr, page_number * PAGE_SIZE, SEEK_SET);
    fread(&buffer, PAGE_SIZE, 1, bkstr);
    int frame_number = get_next_frame_number();
    memcpy(&phys_mem[frame_number * (FRAME_SIZE * sizeof(signed char))], &buffer, FRAME_SIZE); 
    update_tlb(page_number, frame_number);
    update_ptable(page_number, frame_number);

    return frame_number;
}
