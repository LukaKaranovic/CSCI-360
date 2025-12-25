#Makefile for CSCI 360 Assignment 4

CC = gcc
WFLAG = -Wall
CFLAG = -c
DFLAG = -ggdb
IFLAG = -I
LFLAG = -l


INCLUDE = include
SOURCE = src
RESOURCE = resource
BINARY = bin
OBJECT = build
EXAMPLE =example


${BINARY}/simulator: ${OBJECT}/simulator.o ${OBJECT}/ta.o ${OBJECT}/student.o ${OBJECT}/queue.o ${OBJECT}/logger.o
	${CC} ${WFLAG} ${DFLAG} ${OBJECT}/simulator.o ${OBJECT}/ta.o ${OBJECT}/student.o \
		${OBJECT}/queue.o ${OBJECT}/logger.o -o ${BINARY}/simulator -lpthread


${OBJECT}/simulator.o: ${SOURCE}/simulator.c ${INCLUDE}/simulator.h ${INCLUDE}/ta.h ${INCLUDE}/student.h \
	${INCLUDE}/logger.h ${INCLUDE}/config.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} ${IFLAG} ${INCLUDE} ${SOURCE}/simulator.c -o ${OBJECT}/simulator.o


${OBJECT}/ta.o: ${SOURCE}/ta.c ${INCLUDE}/ta.h ${INCLUDE}/queue.h ${INCLUDE}/logger.h ${INCLUDE}/config.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} ${IFLAG} ${INCLUDE} ${SOURCE}/ta.c -o ${OBJECT}/ta.o


${OBJECT}/student.o: ${SOURCE}/student.c ${INCLUDE}/student.h ${INCLUDE}/queue.h ${INCLUDE}/logger.h ${INCLUDE}/config.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} ${IFLAG} ${INCLUDE} ${SOURCE}/student.c -o ${OBJECT}/student.o


${OBJECT}/queue.o: ${SOURCE}/queue.c ${INCLUDE}/queue.h
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} ${IFLAG} ${INCLUDE} ${SOURCE}/queue.c -o ${OBJECT}/queue.o

${OBJECT}/logger.o: ${SOURCE}/logger.c ${INCLUDE}/logger.h ${INCLUDE}/config.h
	${CC} ${WFALG} ${DFLAG} ${CFLAG} ${IFLAG} ${INCLUDE} ${SOURCE}/logger.c -o ${OBJECT}/logger.o

.PHONY: clean run run-example


clean:
	rm -rf --verbose ${BINARY}/* ${OBJECT}/*
	rm -rf --verbose ${RESOURCE}/*
	

run: ${BINARY}/simulator
	cat /dev/null > resource/logs.txt
	${BINARY}/simulator


run-example: ${EXAMPLE}/${BINARY}/simulator
	cat /dev/null > resource/logs.txt
	${EXAMPLE}/${BINARY}/simulator


