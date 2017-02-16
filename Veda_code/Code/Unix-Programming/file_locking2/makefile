both: locker non_locker

locker: locker.c common.h common.o
	gcc -Wall locker.c common.o -o locker

non_locker: non_locker.c common.h common.o
	gcc -Wall non_locker.c common.o -o non_locker

common.o: common.c common.h
	gcc -Wall -c common.c -o common.o

