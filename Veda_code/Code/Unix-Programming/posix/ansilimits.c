/* shows some of the limts that are defined according to ANSI C
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include <limits.h>

main(){
	printf(" Minimum value of signed char = %d\n",SCHAR_MIN);
	printf(" Maximum value of signed char = %d\n",SCHAR_MAX);
	printf(" Maximum value of unsigned char = %d\n",UCHAR_MAX);
	printf(" Minimum value of  char = %d\n",CHAR_MIN);
	printf(" Maximum value of  char = %d\n",CHAR_MAX);

}
	
/* compile the program with and without defining the macro __CHAR_UNSIGNED__
We can find the lints of other datatypes also like this. 
*/
