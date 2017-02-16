.PHONY : netp2_2 clean
netp2_2 :cli1 cli2 srv1 srv3lib1
cli1 cli2 srv1 srv3lib1 :
	gcc cli1.c -o cli1
	gcc cli2.c -o cli2
	gcc srv1.c -o srv1
	gcc srv3.c lib1.c -o srv3lib1
clean :
	rm -rf cli1 cli2 srv1 srv3lib1
