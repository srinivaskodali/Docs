.PHONY : psniffer clean

sniffer : main.o ip.o arp.o rarp.o ip/tcp.o ip/udp.o ip/icmp.o ip/igmp.o psniffer

main.o ip.o arp.o rarp.o ip/tcp.o ip/udp.o ip/icmp.o ip/igmp.o psniffer:
	gcc -c main.c
	gcc -c ip.c
	gcc -c arp.c
	gcc -c rarp.c
	gcc -c ip/tcp.c -o ip/tcp.o
	gcc -c ip/udp.c -o ip/udp.o
	gcc -c ip/icmp.c -o ip/icmp.o
	gcc -c ip/igmp.c -o ip/igmp.o
	gcc main.o ip.o arp.o rarp.o ip/tcp.o ip/udp.o ip/icmp.o ip/igmp.o -o psniffer
	sudo cp psniffer /bin

clean :
	rm -rf $(wildcard *.o ip/*.o p*)	
