/* 
 * This program calculates the number of days needed to 
 * wrap around the jiffies counter
 * Author:Team veda
 * Developed and tested with: Linux kernel version 2.6.10
 * Tested with: Linux kernel version 2.6.29 also
 */
#include <stdio.h>
#include <string.h>
/*
* This program calculates the number of days needed to
* wrap around the jiffies counter
*/

int main()
{
	unsigned long hz_value;
	unsigned long nr_days, max_value;
	
	printf("Enter the value of HZ: ");
	scanf("%u", &hz_value);
	
	printf("Value of HZ is                             : %d\n", hz_value);
	printf("Number of bits in unsigned long jiffies    : %d\n",
		sizeof(unsigned long)*8 );
	memset( &max_value, 0xff, sizeof(unsigned long) );
	nr_days = max_value/(24ul*60ul*60ul*hz_value);
	printf("Max value of the jiffies counter           : %u\n", max_value);
	printf("Max days                                   : %u\n", nr_days);
	printf("WOWOW!!! That is a long long time\n\n");
}
