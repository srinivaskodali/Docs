/* This program about mailserver
Author : IDST
Version : 1.0
*/
#include <stdio.h>
#include "pop3.h"
main()
{
	int ch;
	void sendmail();
	void recvmail();

	while(1){
		printf("\n 1.Send");
		printf("\n 2.Receive");
		printf("\n 3.Exit");
		printf("\n Enter Your Choice [1/2/3]  :");
		scanf("%d",&ch);
		switch(ch){
			case 1: sendmail();
				break;
			case 2: recvmail();
				break;
			case 3: exit(0);
		}
	}
}

void sendmail(){
	char send[100];
	char compose[1024];
	char confirm;

	printf("\n Enter Destination Mail ID : ");
	scanf("%s",send);
	printf("\n Compose the Message: \n");
	scanf("%s",compose);
	printf("\n Sending Message....\n Confirm [y/n] : ");
	getchar();
	scanf("%c",&confirm);
	if(confirm == 'y' || confirm == 'Y')
		pop3send();
	else
		printf("\n Message was cancelled\n");
}

void recvmail()
{
	int msg;

	printf("\n Which date Messages you want to receive : ");
	scanf("%d",&msg);
	pop3recv(msg);
	printf("\n\n");
	
}
