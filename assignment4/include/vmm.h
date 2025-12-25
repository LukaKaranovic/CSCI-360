/**
 * @file vmm.h
 * @author Humayun Kabir, Instructor, CSCI 360, VIU
 * @version 1.0.0
 * @date May 22, 2024
 *
 * Defines the functions for virtual memory manager (vmm).
 *
 */



#ifndef __VMM_HEADER__
#define __VMM_HEADER__



#define PAGE_NUMBER_MASK 0x0000FF00
#define OFFSET_MASK 0x000000FF


int extract_page_number(const int logical_address);
//Extract the page number from the logical address using PAGE_NUMBER_MASK and bitwise shift


int extract_offset(const int logical_address);
//Extract the offset from the logical address using OFFSET_MASK


void init();
//Initialize page table and tlb by calling init_ptable() and init_tlb() functions.



int main(int argc, char** argv);
//Check whether both backing store path name and logical address file name has been supplied or not.
//Open the backing store file in read only and binary mode by calling fopen() library function.
//Open the logical address file in read only mode by calling fopen() library function.
//Initialize physical memory, page table and tlb by calling init().
//Read each logical address from the address file (you may call fgets() and atoi() library functions or fscanf()
//library function) and do the followings
//			Extract the page number from the logical address calling extract_page_number().
//			Extract the offset from the logical address calling extract_offset().
//			Attempt to get the physical frame number from translation look-aside buffer (TLB) first
//			against the page number. Call check_tlb() from "tlb.h".
//			Check for TLB miss. If TLB miss, attempt to get the physical frame number from page table.
//			Call check_ptable() from 'ptable.h".
//			Check for page table fault. If page table fault, load the page from the backing store to a physical frame and
//			update both page table and TLB for future hit. Call load_page() from 'pmemory.h' for this
// 			purpose.
//			Get the value of the byte that is addressed by the frame number and offset at
//			the physical memory. Call get_value() from 'pmemory.h'.
//When the translations of all logical addresses are complete, print the following statistics in separate lines:
//Page Hits, Page Faults, TLB Hits, and TLB Faults.
//Close all opened files.



#endif
