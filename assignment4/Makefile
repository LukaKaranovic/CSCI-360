#Makefile for CSCI 360 Assignment 4

CC = gcc
WFLAG = -Wall
CFLAG = -c
IFLAG = -I
DFLAG = -ggdb


INCLUDE = include
BINARY = bin
OBJECT = build
SOURCE = src
RESOURCE = resource
EXAMPLE = example
INPUT = input
OUTPUT = output


${BINARY}/vmm: ${OBJECT}/vmm.o ${OBJECT}/pmemory.o ${OBJECT}/tlb.o ${OBJECT}/ptable.o
	${CC} ${WFLAG} ${DFLAG} ${OBJECT}/vmm.o ${OBJECT}/pmemory.o ${OBJECT}/tlb.o ${OBJECT}/ptable.o -o ${BINARY}/vmm


${OBJECT}/vmm.o: ${SOURCE}/vmm.c ${INCLUDE}/vmm.h
	${CC} ${WFLAG} ${CFLAG} ${DFLAG} ${IFLAG} ${INCLUDE} ${SOURCE}/vmm.c -o ${OBJECT}/vmm.o


${OBJECT}/pmemory.o: ${SOURCE}/pmemory.c ${INCLUDE}/pmemory.h
	${CC} ${WFLAG} ${CFLAG} ${DFLAG} ${IFLAG} ${INCLUDE} ${SOURCE}/pmemory.c -o ${OBJECT}/pmemory.o


${OBJECT}/tlb.o: ${SOURCE}/tlb.c ${INCLUDE}/tlb.h
	${CC} ${WFLAG} ${CFLAG} ${DFLAG} ${IFLAG} ${INCLUDE} ${SOURCE}/tlb.c -o ${OBJECT}/tlb.o


${OBJECT}/ptable.o: ${SOURCE}/ptable.c ${INCLUDE}/ptable.h
	${CC} ${WFLAG} ${CFLAG} ${DFLAG} ${IFLAG} ${INCLUDE} ${SOURCE}/ptable.c -o ${OBJECT}/ptable.o



.PHONY: clean run run-large run-example run-example-large debug


clean:
	rm -rf --verbose ${BINARY}/*
	rm -rf --verbose ${OBJECT}/*
	rm -rf --verbose ${RESOURCE}/${OUTPUT}/*


run: ${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/addresses.txt
	${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/addresses.txt


run-large: ${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/large_addresses.txt
	${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/large_addresses.txt


run-example: ${EXAMPLE}/${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/addresses.txt
	${EXAMPLE}/${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/addresses.txt


run-example-large: ${EXAMPLE}/${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/large_addresses.txt
	${EXAMPLE}/${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/large_addresses.txt
	
debug: ${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/addresses.txt gdb_commands
	gdb --command=gdb_commands --tui --args ${BINARY}/vmm ${RESOURCE}/${INPUT}/BACKING_STORE.bin ${RESOURCE}/${INPUT}/addresses.txt
	
