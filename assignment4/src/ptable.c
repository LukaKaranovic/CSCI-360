/**
 * @file ptable.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date November 19, 2025
 *
 * Implements the functionalities of the page table. Includes initialization,
 * page table entry searching, invalidating, and updating. Also keeps track of the
 * amount of page hits, faults, and the next free frame.
 */

#include "config.h"
#include "ptable.h"
#include "tlb.h"

int page_table[NUMBER_OF_PAGES];    // Initialization of page table.
int next_free_frame;                // Holds the index of the next free frame
int page_faults;                    // Holds the number of page faults
int page_hits;                      // Holds the number of page hits

/** @brief Initializes the page table and statistics.
 *
 *  Gives every page table entry an associated frame number of -1 (invalid).
 *
 *  @return Void.
 */

void init_ptable() {
    for (int i = 0; i < NUMBER_OF_PAGES; i++) {
        page_table[i] = -1;
    }

    next_free_frame = -1;
    page_faults = 0;
    page_hits = 0;
}

/** @brief Updates a page table entry with a frame number.
 *
 *  Use this function when you want to assign a new frame to a page.
 *
 *  @param page_number The index of the page table entry (page number) to be given the frame number.
 *  @param frame_number The frame number to be given to the entry.
 *  @return Void.
 */

void update_ptable(const int page_number, const int frame_number) {
    page_table[page_number] = frame_number;
}

/** @brief Invalidates a page table entry with a frame number.
 *
 *  Use this when you want to remove a page from a physical frame.
 *
 *  @param frame_number The frame number of the entry to be invaiidated
 *  @return 1 if invalidation was successful, -1 if frame number was not found so no invalidation occurred.
 */

int invalidate_ptable(const int frame_number) {
    int i = 0;
    while (i < NUMBER_OF_PAGES) {
        if (page_table[i] == frame_number) {
            page_table[i] = -1; // invalidate page table entry
            return 1;
        }
        i++;
    }
    return -1; // frame number not found in page table, nothing to invalidate.
}

/** @brief Checks the page table for a page's frame number.
 *
 *  Use this when you want to find out what frame a page is in, or if it is in a frame.
 *
 *  @param page_number The number of the page you are checking.
 *  @return -1 if the page is not in the page table or has an invalid frame (page fault). Otherwise, returns frame number of page.
 */

int check_ptable(const int page_number) {
    if (page_table[page_number] != -1) {
        page_hits++;
        return page_table[page_number];
    } else {
        page_faults++;
        return -1;
    }
}

/** @brief Gets the number of page faults.
 *
 *  @return The number of page faults.
 */

int get_page_faults() {
    return page_faults;
}

/** @brief Gets the number of page hits.
 *
 *  @return The number of page hits.
 */

int get_page_hits() {
    return page_hits;
}

/** @brief Gets the frame numnber of the next free frame.
 *
 *  Uses FIFO page replacement algorithm, so next_free_frame starts at frame 0 and increments until all frames
 *  are full, then it replaces the oldest frame.
 *
 *  Invalidates the corresponding entries in page table and TLB for that frame.
 *
 *  @return The frame number of the next free frame.
 */

int get_next_frame_number() {
    next_free_frame = (next_free_frame + 1) % NUMBER_OF_FRAMES;
    invalidate_ptable(next_free_frame);
    invalidate_tlb(next_free_frame);
    return next_free_frame;
}
