#!/bin/bash

VPATH = /usr/lib/ source include
#vpath = %.c source
#vpath = %.h include
CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -L/usr/lib
LIBS = -lm

objects=array.o ipv6.o list.o sort.o leetcode.o main.o 

main:$(objects)
	${CC} ${LIBS} ${LDFLAGS} -o daring $^ 

#main.o:main.c list.h public.h ipv6.h array.h sort.h leetcode.h
#	${CC} $(CFLAGS) -Iinclude -c $< 

#list.o: list.c list.h public.h
#	${CC} $(CFLAGS) -Iinclude -c $< 

#ipv6.o: ipv6.c ipv6.h public.h
#	${CC} $(CFLAGS) -Iinclude -c $< 

#array.o: array.c array.h public.h
#	${CC} $(CFLAGS) -Iinclude -c $< 

#sort.o: sort.c sort.h array.h public.h
#	${CC} $(CFLAGS) -Iinclude -c $< 

#leetcode.o: leetcode.c leetcode.h array.h public.h
#	${CC} $(CFLAGS) -Iinclude -c $< 

%.o:%.c
	${CC} $(CFLAGS) -Iinclude -c $< 
	
.PHONY:clean
clean:
	-rm -rf daring $(objects)