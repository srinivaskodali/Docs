// shows some details on how memory is managed at OS level
// Version : 1.0
// Author : Team -C

main(){
        void *p;
	int i;
	i=0;
	while(i <100){
	p = (void *)	malloc(10000000);
		printf("%x check memmap in /proc \n",p);
		getchar();
	}
}
