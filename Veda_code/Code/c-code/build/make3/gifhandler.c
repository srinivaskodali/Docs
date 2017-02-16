
/* This module takes care of gif files 
Version : 1.0
Author : Team -C
*/

# include <string.h>
# include "handlers.h"

// function returns whether this can handle the file or not

int canHandle(char *filename){
	int len;
	char *end;
	printf(" Checking whether I can handle %s or not \n",filename);
	len = strlen(filename);
	end = filename + (len -3);
	printf(" end = %s\n",end);
	// just for testing purpose, in the real code the file need to be
	// opened and we need to check for magic no's.
	if(strcmp(end,"gif") == 0)
		return TRUE;
	else
		return FALSE;
}

int drawImage(char *filename){
	if( canHandle(filename)){
		printf(" How is this image %s \n",filename);
		return TRUE;
	}
	else
		return FALSE;
}

int savefile(char *newfilename ){
	printf(" file saved by gif handler \n");
	return TRUE;
}

