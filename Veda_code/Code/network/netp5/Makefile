.PHONY: 5_etc_services clean
5_etc_services:hostdet hostdet1 hostdet2 servdet servdet1
hostdet hostdet1 hostdet2 servdet servdet1 :                                         
	gcc hostdet.c -o hostdet
	gcc hostdet1.c -o hostdet1
	gcc hostdet2.c -o hostdet2
	gcc servdet.c -o servdet 
	gcc servdet1.c -o servdet1 
clean:
	rm -rf hostdet hostdet1 hostdet2 servdet servdet1
