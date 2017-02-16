
/* This program uses the library functions which rae declared in 
the header file tree.h
Version : 1.0
Author : Team -C
*/


# include <stdio.h>
# include "tree.h"

void printlist(TreeNode *node){
	TreeNode **list,*nodeptr;
	int ccount,i;
	ccount = getChildCount(node);
	list = getChildNodes(node);
	if(list == NULL)
		return;
	nodeptr = *list;
	for(i=0;i<ccount; i++){
		printf(" Data in Node = %d\n",nodeptr->data);
		nodeptr++;
	}
}
main(){
 TreeNode * root,*temp1,*temp2;
 root = createRootNode();
 printf(" root node = %x", root);
  temp1 = addNode(root);
  temp1->data = 1;
  temp2=addNode(root);
  temp2->data=2;
  temp2=addNode(root);
  temp2->data=3;
  temp2=addNode(root);
  temp2->data=4;
  temp2=addNode(root);
  temp2->data=5;
  printf(" no of child nodes for root %d\n",getChildCount(root));
  temp2=addNode(temp1);
  temp2->data=100;
  temp2=addNode(temp1);
  temp2->data=200;
  printf(" no of child nodes for temp1 %d\n",getChildCount(temp1));
  printlist(root);
  printlist(temp1);
}
