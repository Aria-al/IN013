CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CC = gcc

main : main.o EuclideAlgos.o InversionMatrice.o SystemChinois.o 
	$(CC) -o $@ $(CFLAGS) $^ -lm

%.o:%.c InversionMatrice.h SystemChinois.h EuclideAlgos.h
	$(CC)  $(GCC_FLAGS) -c  $<