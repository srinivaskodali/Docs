main(){
	char a[10]="abcdefghi";
	char b[10];
	long l;
	for(l=0;l<9999999;l++)
	mymemcopy(a,b,10);
	printf("%s\n",b);
}
