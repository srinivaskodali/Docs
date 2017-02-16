/* src = 8(%ebp)
   dest =12(%ebp)
   count =16(%ebp)
*/

void mymemcopy(char *src,char *dest, int count){
	__asm__("movl 8(%ebp),%esi");
	__asm__("movl 12(%ebp),%edi");
	__asm__("movl 16(%ebp),%ecx");
	__asm__("cld"); // use std instead of cld and see the result
	__asm__("repnz movsb ");
}
