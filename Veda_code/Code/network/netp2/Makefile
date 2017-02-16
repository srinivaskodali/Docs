.PHONY :  2_thread_tcp clean
2_thread_tcp : cli1 cli2 srv1 srv2 srv3 srv4 srv5

cli1 cli2 srv1 srv2 srv3 srv4 srv5 :
	gcc cli1.c -o cli1
	gcc cli2.c -o cli2
	gcc srv1.c -o srv1
	gcc srv2.c -o srv2
	gcc srv3.c -o srv3
	gcc srv4.c -lpthread -o srv4 
	gcc srv5.c -lpthread -o srv5

clean:
	rm -rf cli1 srv2 srv5 cli2 srv3 srv1 srv4

