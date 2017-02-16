
// Here is the implementation of a binary tree , we can represent
// any type of data using binary tree.
// Version : 1.0
// Author : Team - C.

# include <stdio.h>
struct data{
	int somedata;
	struct data *left;
	struct data *right;
};
typedef struct data BinaryTree;

void addNodeToTree(BinaryTree *root){
	int newdata;
	BinaryTree *temp,*wheretoadd;
	printf(" Enter data to be added :");
	scanf("%d",&newdata); // ensure that data entered is not 0.
// if root is empty put the data item here.
	if(root->somedata == 0){
		root->somedata=newdata;
		return;
	}
	else{
		temp = (BinaryTree *) malloc(sizeof(BinaryTree));
		temp->somedata =  newdata;
		temp->left = NULL;
		temp->right = NULL;
		// now let us decide where to add this node.
		wheretoadd = root;
		while(1){
			if(newdata < wheretoadd->somedata){
				// add as left
				if (wheretoadd->left ==NULL){
					wheretoadd->left = temp;
					break;
				}
				else
					wheretoadd=wheretoadd->left;
			}
			else{
				// add as right
				if (wheretoadd->right ==NULL){
					wheretoadd->right = temp;
					break;
				}
				else
					wheretoadd=wheretoadd->right;
			}
		}
	}	
}	
// we prefer iterative algorithms over recursive .
void searchNode( BinaryTree * root, int n){
	while(1){
		if(root ->somedata == n){
			printf(" data found\n");
			return;
		}
		if(n < root->somedata ){
			if (root->left == NULL)
				return;
			root = root ->left;
		}
		else{
			if(root->right == NULL)
				return;
			root = root ->right;
		}
	}
}

main(){
	int nono;
	int i;
	BinaryTree *root = (BinaryTree *) malloc(sizeof(BinaryTree));
	root->left=NULL;
	root->right=NULL;
	root->somedata = 0; // assume 0 is invalid data.
	printf(" Enter no of dataitems you want to store:");
	scanf("%d",&nono);
	for(i=0;i<nono;i++)
		addNodeToTree(root);
	system("clear");
	for(i=0;i<4;i++){
		printf(" Enter the no to be searched :");
		scanf("%d",&nono);
		searchNode(root,nono);
	}
}


// When we build an application like windows explorer we need to store the
// data in tree form . Try to define a structure which can be used to
// represent the information of file in tree form. Assume a tree will have
// a node and the node may contain any no of sub-node.

