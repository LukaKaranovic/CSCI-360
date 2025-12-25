/**
 * @file tlb.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date November 19, 2025
 *
 * Implements the functionalities of the translation lookaside buffer (TLB). Includes initialization,
 * TLB entry searching, invalidating, and updating. Also keeps track of the
 * amount of TLB hits, faults, and the next free entry.
 */

#include "config.h"
#include "tlb.h"

tlb_entry_t tlb[NUMBER_OF_TLB_ENTRIES];     // Array to hold all TLB entries.
int next_free_index;                        // Tracks the next free TLB index.
int tlb_hits;                               // Holds the number of TLB hits
int tlb_faults;                             // Holds the number of TLB faults

/** @brief Initalizes the translation lookaside buffer (TLB) and TLB statistics.
 *
 *  Initializes every TLB entry struct for each TLB entry. Each TLB entry will have a page number
 *  and frame number of -1. Its validity will be 0 (invalid).
 *
 *  @return The number of page faults.
 */

void init_tlb() {
    for (int i = 0; i < NUMBER_OF_TLB_ENTRIES; i++) {
        tlb[i].page_number = -1;
        tlb[i].frame_number = -1;
        tlb[i].valid = 0;
    }
    next_free_index = -1;
    tlb_hits = 0;
    tlb_faults = 0;
}

/** @brief Updates a TLB entry with a given page number and frame number.
 *
 *  Finds the next free TLB entry and updates it with the given page number and frame number,
 *  associating them with each other. This entry is marked as valid.
 *
 *  Use this after you have loaded a page or found the page in the page table after a TLB miss.
 *
 *  @return Void.
 */

void update_tlb(const int page_number, const int frame_number) {
    int index = get_next_tlb_index();
    tlb[index].page_number = page_number;
    tlb[index].frame_number = frame_number;
    tlb[index].valid = 1;
}

/** @brief Invalidates a TLB entry with the corresponding frame number.
 *
 *  Looks for the TLB entry with the corresponding frame number and invalidates it.
 *
 *  Use this function when you are replacing a page frame with a new page.
 *
 *  @param frame_number The number of the frame being replaced.
 *  @return 1 if the invalidation was successful, -1 if no invalidation occurred.
 */

int invalidate_tlb(const int frame_number) {
    for (int i = 0; i < NUMBER_OF_TLB_ENTRIES; i++) {
        if (tlb[i].frame_number == frame_number) {
            tlb[i].valid = 0;
            return 1; // found corresponding tlb entry, invalidating it.
        }
    }
    return -1; // could not find tlb entry, no invalidation occurred.
}

/** @brief Checks if there is a TLB entry for a particular page.
 *
 *  Looks for the TLB entry with the corresponding page number and retrieves the corresponding frame number it is in.
 *  Will not retrieve the frame number if the TLB entry is invalid. Increments TLB hits if there is a valid entry, otherwise
 *  increments TLB faults.
 *
 *  Use this when checking if TLB has page's frame number.
 *
 *  @param page_number The number of the page being checked.
 *  @return -1 if TLB entry not found (TLB fault). Otherwise, returns the frame number of the page.
 */

int check_tlb(const int page_number) {
    for (int i = 0; i < NUMBER_OF_TLB_ENTRIES; i++) {
        if ((tlb[i].valid == 1) && (tlb[i].page_number == page_number)) {
            tlb_hits++;
            return tlb[i].frame_number;
        } 
    }
    tlb_faults++;
    return -1;
}

/** @brief Gets the number of TLB faults.
 *
 *  @return The number of TLB faults.
 */

int get_tlb_faults() {
    return tlb_faults;
}

/** @brief Gets the number of TLB hits.
 *
 *  @return The number of TLB hits.
 */

int get_tlb_hits() {
    return tlb_hits;
}

/** @brief Gets the index of the next free TLB entry.
 *
 *  Uses FIFO TLB entry replacement algorithm, so next_free_index starts at entry 0 and increments until all entries
 *  in TLB are full, then it replaces the oldest entry.
 *
 *  @return The index of the next free TLB entry.
 */

int get_next_tlb_index() {
    next_free_index = (next_free_index + 1) % NUMBER_OF_TLB_ENTRIES;
    return next_free_index;
}

