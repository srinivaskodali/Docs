
/* This modules provides the implementataion of ui related functions 
Version : 1.0
Author : Team -C
*/

# include <stdio.h>
# include "handlers.h"
static char filename[100];

void handleMenuEvent(int choice){
	printf(" Enter file name :");
	scanf("%s",filename);
	switch(choice){
		case 1:
			if(canHandle(filename))
				drawImage(filename);	
			else
				printf(" we cannot handle this file\n");
			break;
		case 2:
			savefile(filename);
			break;
	}
	printf(" ----------------------------------\n");
}

void displayMenu(){
	int choice;
	while(1){
		printf(" 1: Show Image \n");
		printf(" 2: Save Image \n");
		printf(" 3: Exit \n");
		printf(" Choice:");
		scanf("%d",&choice);
		if(choice == 3)
			exit(0);
		handleMenuEvent(choice);
	}
}

main(){
	displayMenu();
}
