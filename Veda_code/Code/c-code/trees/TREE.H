/* To show how libraries can be implemented
Version : 1.0
Author : Team -C
*/


typedef struct TN{
	int data ; // to make it generic tree we can use a pointer to void.
	 struct TN **childlist; // pointer to a list of pointers.
	int childcount; // no of nodes
}TreeNode;



TreeNode *createRootNode();
TreeNode *addNode(TreeNode *parent);
int getChildCount(TreeNode *node);
// add code for removeNode(TreeNode *parent, TreeNode *child);
// add code for destroyTree( TreeNode *root);
TreeNode ** getChildNodes(TreeNode *parent);

