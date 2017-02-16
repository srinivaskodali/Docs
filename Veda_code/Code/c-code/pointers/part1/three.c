// about strings (char arrays terminated by \0
// Version : 1.0
// Author : Team -C

main(){

	char a[] = "abcdef";
	char *k;
	k=&a[0]; // same as k= a;
	while (*k != '\0')
		putchar(*k++);
}
