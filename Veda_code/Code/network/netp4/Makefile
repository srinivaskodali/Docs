.PHONY : 4_udp clean

4_udp: cli1 cli2 cli31 cli3 srv1 srv2 srv3 srv
cli1 cli2 cli31 cli3 srv1 srv2 srv3 srv:
	gcc cli1.c -o cli1
	gcc cli2.c -o cli2
	gcc cli31.c -o cli31
	gcc cli3.c -o cli3
	gcc srv1.c -o srv1
	gcc srv2.c -o srv2
	gcc srv3.c -o srv3
	gcc srv.c -o srv
clean:
	rm -rf cli1 cli2 cli31 cli3 srv1 srv2 srv3 srv


