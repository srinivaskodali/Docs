
/* This program uses the library functions which reached declared in 
the header file tree.h
Version : 1.0
Author : Team -C
*/


# include <stdio.h>
# include "tree.h"

void printlist(TreeNode *node){
	TreeNode **list;
	TreeNode *nodeptr;
	int ccount,i;
	ccount = getChildCount(node);
	list = getChildNodes(node);
	printf(" no of child nodes = %d\n",ccount);
	if(list == NULL)
		return;
	for(i=0;i<ccount; i++){
		printf(" Data in Node = %d\n",(*list)->data);
		list++;
	}
}
main(){
 TreeNode * root,*temp1,*temp2;
 root = createRootNode();
 printf(" root node = %x", root);
  temp1 = addNode(root);
  temp1->data=1;
  temp1 = addNode(root);
  temp1->data=2;
  temp1 = addNode(root);
  temp1->data=3;
  temp1 = addNode(root);
  temp1->data=4;
  temp2 = addNode(temp1);
   temp2->data=1000;
  temp2 = addNode(temp1);
   temp2->data=2000;
  temp2 = addNode(temp1);
   temp2->data=3000;
  printlist(root);
  printlist(temp1);
}
