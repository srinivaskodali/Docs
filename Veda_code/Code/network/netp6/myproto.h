/* Sample header showing the details of our own protocol header 
Version: 1.0
Author: Team -C
*/

# define IPPROTO_MYPROTO 100

struct myphdr{
	short source_app;
	short dest_app;
	short data_len;
};
