.PHONY :1_tcp clean
1_tcp: cli1 cli2 cli3 srv1 srv2 srv3
cli1 cli2 cli3 srv1 srv2 srv3:
	gcc cli1.c  -o cli1
	gcc cli2.c  -o cli2
	gcc cli3.c  -o cli3
	gcc srv1.c  -o srv1
	gcc srv2.c  -o srv2
	gcc srv3.c  -o srv3
clean:
	rm -rf cli1 cli2 cli3 srv1 srv2 srv3

