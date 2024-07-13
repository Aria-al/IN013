CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CC = gcc

main : main.o EuclideAlgos.o InversionMatrice.o SystemChinois.o SuiteDetermine.o PolynomeCaract.o
	$(CC) -o $@ $(CFLAGS) $^ -lm
	rm *.o

%.o:%.c InversionMatrice.h SystemChinois.h EuclideAlgos.h SuiteDetermine.h PolynomeCaract.h
	$(CC)  $(GCC_FLAGS) -c  $<