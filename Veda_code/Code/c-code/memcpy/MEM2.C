void mymemcopy(char *src,char *dest, int count){
	int i;
	for(i=0;i<count;i++){
		*dest=*src;
		dest++;
		src++;
	}
}
