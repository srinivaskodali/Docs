.PHONY:6_icmp clean
6_icmp:cli1 srv1 srv2
cli1 srv1 srv2:
	gcc cli1.c -o cli1
	gcc srv1.c -o srv1
	gcc srv2.c -o srv2
clean:
	rm -rf cli1 srv1 srv2
