/**
 * @file vmm.c
 * @author Luka Karanovic, 665778833, F25N01, CSCI 360, VIU
 * @version 1.0.0
 * @date November 19, 2025
 *
 * Plays the role of the Virutal Memory Manager (VMM) in this memory management application.
 * Has helper functions to extract the page number and offset from an address, initialize
 * page table and TLB, and to execute the routine of the VMM.
 */

#include <stdio.h>

#include "config.h"
#include "ptable.h"
#include "pmemory.h"
#include "tlb.h"
#include "vmm.h"

/** @brief Extracts the page number from a given a logical address.
 *
 *  Uses a mask to do bitwise operation to extract the page number. Shifts it right 8 bits
 *  as offset is 8 bits, this is to get the correct integer value.
 *
 *  @param logical_address The logical address to be extracted.
 *  @return The extracted page number value.
 */

int extract_page_number(const int logical_address) {
    return (logical_address & PAGE_NUMBER_MASK) >> 8;
}

/** @brief Extracts the offset from a given a logical address.
 *
 *  Uses a mask to do bitwise operation to extract the offset.
 *
 *  @param logical_address The logical address to be extracted.
 *  @return The extracted offset value.
 */

int extract_offset(const int logical_address) {
    return (logical_address & OFFSET_MASK);
}

/** @brief Initializes the page table and TLB.
 *
 *  Calls initialization routines for page table and TLB.
 *
 *  @return Void.
 */

void init() {
    init_ptable();
    init_tlb();
}

/** @brief Executes the routine of the VMM, the main routine of this memory management application.
 *
 *  First, opens up backing store and then the file that contains the logical addresses.
 *  For each address in the logical address file, scans for it and extracts the page number and the offset.
 *  Then, uses page number to check for frame number. First in TLB, if TLB miss, then page table, if page table miss,
 *  then loads the page from memory and updates both the page table and TLB. Once the frame number has been obtained,
 *  the VMM finds the physical memory location and extracts the value (signed char byte) from it. It then converts it to
 *  an integer and displays it. Statistics such as number of TLB hits and faults and number of page table hits and faults
 *  are displayed.
 *
 *  @param argc The count of arguments passed upon execution of file.
 *  @param argv The array of arguments passed upon execution of file.
 *  @return 0 if exited normally. Non-zero if any errors occured during execution.
 */

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Invalid amount of arguments. Proper usage is bin/vmm <path_to_backing_store> <path_to_logical_addresses>.\n");
        return 1;
    }

    FILE* bkstr = fopen(argv[1], "r");
    if (bkstr == NULL) {
        printf("Error opening backing store file.\n");
        return 2;
    }
    FILE* addresses = fopen(argv[2], "r");
    if (addresses == NULL) {
        printf("Error opening logical address file.\n");
        return 3;
    }
    init();
    int curr_address;

    while (fscanf(addresses, "%d", &curr_address) == 1) {
        int page_number = extract_page_number(curr_address);
        int offset = extract_offset(curr_address);
        int frame_number = check_tlb(page_number);
        if (frame_number == -1) { // tlb miss
            frame_number = check_ptable(page_number);
            if (frame_number == -1) { // page table miss -> page fault
                frame_number = load_page(page_number, bkstr);
            } 
        }
        signed char value = get_value(frame_number, offset);
        printf("%d\n", (int)value);
    }
    printf("Page Hits = %d\n", get_page_hits());
    printf("Page Faults = %d\n", get_page_faults());
    printf("TLB Hits = %d\n", get_tlb_hits());
    printf("TLB Faults = %d\n", get_tlb_faults());

    fclose(bkstr);
    fclose(addresses);
    return 0;
}





