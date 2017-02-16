
/* Here is a generic code for representing data as a tree.
Version : 1.0
Author : Team -C
Remarks : go thr'u the code thoroughly and try to optimize the code

Hint : can we use  realloc ??
We need not write the comments like we did in this case.
add the algorithm we used as a comment before the function
addNode.
*/

# include <stdio.h>
# include "tree.h"


// pretty simple, create a node and return pointer to it.
TreeNode * createRootNode(){
	TreeNode *root;
	root= (TreeNode *) malloc( sizeof(TreeNode));
	if(root !=NULL){
		root->childlist=NULL;
		root->childcount=0;
	}
	return root; // if no memory is left we will be returning NULL
}
	
TreeNode *addNode(TreeNode *parent){
	TreeNode *child;
	TreeNode **liststart;
	TreeNode **oldliststart;
	TreeNode **temp1,**temp2;
	int i;
	if(parent == NULL)
 // we need not create a child if parent is not existing
		return NULL;
	child= (TreeNode *) malloc( sizeof(TreeNode));
	if(child ==NULL)
		return NULL;
// initially when child is created it will not be holding childern.
// it's born just now ??
	child->childlist=NULL;
	child->childcount=0;
// if there are no child nodes till now . create memory are where we can 
// store pointer to child node.
	if(parent->childcount == 0){
	liststart = (TreeNode **) malloc(sizeof(TreeNode *));
		parent->childcount=1;
		*liststart = child;
		parent ->childlist =liststart;
	}
	else{
		parent->childcount++;
		oldliststart=parent->childlist;	
	printf(" *oldlist start  %x *\n",oldliststart);
		i = parent->childcount;
	liststart = (TreeNode **) malloc(sizeof(TreeNode*)* i);
	printf(" *newlist start  %x *\n",liststart);
// move to the end of list and put the new child at the end.
		temp1=liststart;
		temp2=oldliststart;
		for(i=1;i<parent->childcount;i++){
			*temp1 = *temp2;
			temp1++;
			temp2++;
		}
		*temp1=child;
		parent->childlist=liststart;
		// get rid of oldlist
		free(oldliststart);
         }
printf(" \nafter adding list start =%x",parent->childlist);
printf("\n pointer in list start =%x",*(parent->childlist));
	return(child);
}
int getChildCount(TreeNode *node){
	return node->childcount;
}
// add code for removeNode(TreeNode *parent, TreeNode *child);
// add code for destroyTree( TreeNode *root);
TreeNode ** getChildNodes(TreeNode *node){
	return node->childlist;
}



