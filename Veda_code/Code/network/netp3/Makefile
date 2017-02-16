
.PHONY : 3_fteller_tcp clean


3_fteller_tcp : lib1.o client server


lib1.o client server :	
	gcc -c lib1.c -o lib1.o
	gcc cli1.c lib1.o -o client
	gcc fteller.c lib1.o -o server

clean:
	rm -rf client lib1.o server



