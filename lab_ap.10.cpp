//Binary Tree with points coordinates(x, y, z); Deleting nodes with one children element, finding element the closest to (0 , 0 , 0;
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeData {
	int x;
	int y;
	int z;
}Data;

typedef struct TreeNode {
	Data data;
	struct TreeNode *left, *right;
}Node;

Node* root;

int getData(Data *data) {
	static int num = 1;
	printf("%d x element: ", num);
	if (!scanf_s("%d", &data->x))
		return 0;
	printf("%d y element: ", num);
	scanf_s("%d", &data->y);
	printf("%d z element: ", num++);
	scanf_s("%d", &data->z);
	return 1;
}

void freeNodeMemory(Node* node) {
	free(node);
	node = NULL;
}

Node* newNode(void) {
	Node* element;
	Data buff;
	if(!getData(&buff))
		return NULL;
	element = (Node*)malloc(sizeof(Node));
	element->data = buff;
	element->left = element->right = NULL;
	return element;
}

void addNode(Node* pnew, Node** tempRoot) {
	Node* proot = *tempRoot;
	int compare;

	if (proot == NULL) {
		*tempRoot = pnew;
		return;
	}

	compare = (proot->data.x > pnew->data.x) ? -1 : 1;
	if (proot->data.x == pnew->data.x) {

		compare = (proot->data.y > pnew->data.y) ? -1 : 1;
		if (proot->data.y == pnew->data.y) {

			compare = (proot->data.z > pnew->data.z) ? -1 : 1;
			if(proot->data.z == pnew->data.z)
				freeNodeMemory(pnew);
			else
				if (compare > 0)
					addNode(pnew, &proot->left);
				else
					addNode(pnew, &proot->right);
		}
		else
			if (compare > 0)
				addNode(pnew, &proot->left);
			else
				addNode(pnew, &proot->right);
	}
	else
		if (compare > 0)
			addNode(pnew, &proot->left);
		else
			addNode(pnew, &proot->right);
}

void printTree(Node* root) {
	if (root == NULL)
		return;
	printTree(root->right);
	printf("%d - %d - %d\n", root->data.x, root->data.y, root->data.z);
	printTree(root->left);
}

void freeTree(Node* root) {
	if (root == NULL)
		return;
	freeTree(root->left);
	freeTree(root->right);
	freeNodeMemory(root);
}

void freeOneChildrenElements(Node* proot, Node* parent = NULL) {
	Node* children = proot;
	if (children == NULL) return;
	if (children->left == NULL && children->right == NULL) return;
	freeOneChildrenElements(children->left, children);
	freeOneChildrenElements(children->right, children);

	if (children->left == NULL && children->right != NULL) {
		Node* temp = children->right;
		
		if (children == parent->right) {
			parent->right = temp;
			freeNodeMemory(children); 
			children = temp;
		}
		else {
			parent->left = temp;
			freeNodeMemory(children); 
			children = temp;
		}
	}

	if (children->left != NULL && children->right == NULL) {
		Node* temp = children->left;

		if (children == parent->right) {
			parent->right = temp;
			freeNodeMemory(children);
			children = temp;
		}
		else {
			parent->left = temp;
			freeNodeMemory(children);
			children = temp;
		}
	}
	
	
	
	
}

int treeHeight(Node* root) {
	int leftHight, rightHight;
	if (root == NULL) return 0;
	leftHight = treeHeight(root->left);
	rightHight = treeHeight(root->right);
	return leftHight > rightHight ? leftHight + 1 : rightHight + 1;
}

void showLevels(void) {
	int level;
	printf("Level: ");
	for (level = 1; level <= treeHeight(root); level++)
		printf("%-8d", level);
	printf("\n");
}

void showTree(Node* root, int level) {
	if (level == 1) showLevels();
	if (root == NULL) return;
	showTree(root->right, level + 1);
	printf("%*c %d %d %d\n", level * 8, ' ', root->data.x, root->data.y, root->data.z);
	showTree(root->left, level + 1);
}

Node* findTheClosestPointToStart(Node* root) {
	Node* proot = root, *pnext;
	int min = proot->data.x + proot->data.y + proot->data.z;
	int tempMin = 0; Node* minimum = proot;
	Node ** stack;
	stack = (Node**)calloc(treeHeight(root), sizeof(Node*));
	int i = 0;
	while (proot != NULL) {
		if (proot->left != NULL) {
			pnext = proot->left;
			if (proot->right != NULL)
				stack[++i] = proot->right;
		}
		else
			if (proot->right != NULL)
				pnext = proot->right;
			else
				pnext = stack[i--];
		tempMin = proot->data.x + proot->data.y + proot->data.z;
		
		if (tempMin < min) {
			min = tempMin;
			minimum = proot;
		}
		proot = pnext;
	}
	return minimum;
}




int main(void) {
	Node* node;
	puts("\tCreating the tree..");
	while ((node = newNode()) != NULL)
		addNode(node, &root);
	puts("\n\tCreated tree:\n");
	printTree(root);
	printf("\n");
	showTree(root, 1);
	printf("\n\n");
	Node* closest = findTheClosestPointToStart(root);
	printf("The closest point to start: %d - %d -%d\n", closest->data.x, closest->data.y, closest->data.z);
	puts("\n\tDeleting all nodes with one children element");
	freeOneChildrenElements(root);
	showTree(root, 1);
	freeTree(root); root = NULL;
	return 0;
}

































//#include <stdlib.h>
//
//typedef struct data
//{
//	int x;
//	// int y;
//	// int z;
//}DATA;
//typedef  struct treeNode
//{
//	DATA field;
//	struct treeNode *left, *right;
//
//
//}treeNode;
//treeNode*  Root;
//
//DATA* setData()
//{
//	DATA *new = (DATA*)malloc(sizeof(DATA));
//	printf("\n Input x ");
//	scanf("%d", &new->x);
//	getchar();
	/*
		printf("\n Input y ");
		scanf("%d" , &new->y);
		getchar();
		printf("\n Input z ");
		scanf("%d" , &new->z);
		getchar();
//		*/
//	return new;
//}
//
//
//treeNode* newNode(void)
//{
//	treeNode *newElem;
//	newElem = (treeNode*)malloc(sizeof(treeNode));
//
//	newElem->field = *setData();
//	newElem->left = newElem->right = NULL;
//	return  newElem;
//
//}
//
//treeNode* Search(treeNode *start, DATA* data) {
//	if (start == NULL)
//	{
//		return NULL;
//	}
//
//	if (start->field.x == data->x)
//	{
//		return start;
//	}
//
//
//	if (data->x < start->field.x)
//	{
//		Search(start->left, data);
//	}
//
//	if (data->x > start->field.x)
//	{
//		Search(start->right, data);
//	}
//
//
//
//}
//
//void AddNode(treeNode* newNode, treeNode** treeRoot)
//{
//	treeNode* pointerToRoot = *treeRoot;
//	if (pointerToRoot == NULL)
//	{
//		*treeRoot = newNode;
//
//		return;
//	}
//	/*
//	if(Search(Root , &newNode->field) !=NULL)
//	{
//		free(newNode);
//		return;
//	}
//*/
//	if (newNode->field.x > pointerToRoot->field.x)
//		AddNode(newNode, &pointerToRoot->right);
//
//	if (newNode->field.x < pointerToRoot->field.x)
//		AddNode(newNode, &pointerToRoot->left);
//
//}
//
//void PrintTree(treeNode *proot)
//{
//	if (proot == NULL)
//		return;
//	else
//	{
//		printf("\n x : %d", proot->field.x);
//		PrintTree(proot->left);
//
//		PrintTree(proot->right);
//	}
//}
//void deleteNode()
//{
//	if (Root == NULL)
//		return;
//
//	if ((Root->left == NULL) && (Root->right != NULL))
//	{
//		Root = Root->right;
//		free(Root->right);
//		return;
//	}
//	if ((Root->right == NULL) && (Root->left != NULL))
//	{
//		Root = Root->left;
//		free(Root->left);
//		return;
//	}
//	deleteNode(Root->left);
//	deleteNode(Root->right);
//
//}





