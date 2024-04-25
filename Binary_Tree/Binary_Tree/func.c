#include "func.h"

TreeNode* CreateNode(int value) {
	TreeNode* ResultNode = (TreeNode*)malloc(sizeof(TreeNode));

	if (ResultNode == NULL)
		return ResultNode;
	ResultNode->data = value;
	ResultNode->LeftBranch = NULL;
	ResultNode->RightBranch = NULL;
	return ResultNode;
}

BinaryTree* CreateTree() {
	BinaryTree* Res = (BinaryTree*)malloc(sizeof(BinaryTree));
	if (Res == NULL)
		return NULL;
	Res->Root = NULL;
	return Res;
}

int SearchElement(BinaryTree* tree, int value) {
	if (tree == NULL)
		return -1;
	printf("\n");
	TreeNode* CurrentNode = tree->Root;
	while (1) {
		if (value == CurrentNode->data) {
			Temple = CurrentNode;
			printf("%d.\n\n", CurrentNode->data);
			return 0;
		}
		else if (value >= CurrentNode->data && CurrentNode->RightBranch != NULL) {
			printf("%d -> ", CurrentNode->data);
			CurrentNode = CurrentNode->RightBranch;
		}
		else if (value >= CurrentNode->data && CurrentNode->RightBranch == NULL)
			return 1;
		else if (value < CurrentNode->data && CurrentNode->LeftBranch != NULL) {
			printf("%d -> ", CurrentNode->data);
			CurrentNode = CurrentNode->LeftBranch;
		}
		else
			return 1;
	}
}

void AddElement(BinaryTree* tree, int value) {
	if (tree == NULL)
		return;
	if (tree->Root == NULL) {
		tree->Root = CreateNode(value);
		return;
	}
	TreeNode* CurrentNode = tree->Root;
	while (1) {
		if (value >= CurrentNode->data && CurrentNode->RightBranch != NULL)
			CurrentNode = CurrentNode->RightBranch;
		else if (value >= CurrentNode->data && CurrentNode->RightBranch == NULL) {
			CurrentNode->RightBranch = CreateNode(value);
			return;
		}
		else if (value < CurrentNode->data && CurrentNode->LeftBranch != NULL)
			CurrentNode = CurrentNode->LeftBranch;
		else {
			CurrentNode->LeftBranch = CreateNode(value);
			return;
		}
	}
}

void PrintTree(TreeNode* tree, int level) {
	int i;
	if (tree == NULL)
		return;
	PrintTree(tree->RightBranch, level + 1);
	for (i = 0; i < level; i++)
		printf("\t");
	printf("%d\n", tree->data);
	PrintTree(tree->LeftBranch, level + 1);
}

void FreeTree(TreeNode* tree) {
	if (tree == NULL)
		return;
	FreeTree(tree->LeftBranch);
	FreeTree(tree->RightBranch);
	free(tree);
}

TreeNode* minValue(TreeNode* tree) {
	TreeNode* CurrentNode = tree;
	while (CurrentNode->LeftBranch != NULL)
		CurrentNode = CurrentNode->LeftBranch;
	return CurrentNode;
}

TreeNode* DeleteElement(TreeNode* tree, int value) {
	if (tree == NULL)
		return tree;
	if (value < tree->data)
		tree->LeftBranch = DeleteElement(tree->LeftBranch, value);
	else if (value > tree->data)
		tree->RightBranch = DeleteElement(tree->RightBranch, value);
	else {
		if (tree->LeftBranch == NULL) {
			TreeNode* temp1 = tree->RightBranch;
			free(tree);
			return temp1;
		}
		else if (tree->RightBranch == NULL) {
			TreeNode* temp2 = tree->LeftBranch;
			free(tree);
			return temp2;
		}
		TreeNode* tmp = minValue(tree->RightBranch);
		tree->data = tmp->data;
		tree->RightBranch = DeleteElement(tree->RightBranch, tmp->data);
	}
	return tree;
}

void TestTree(BinaryTree* tree) {
	AddElement(tree, 8);
	AddElement(tree, 3);
	AddElement(tree, 10);
	AddElement(tree, 1);
	AddElement(tree, 6);
	AddElement(tree, 4);
	AddElement(tree, 7);
	AddElement(tree, 14);
	AddElement(tree, 13);
	AddElement(tree, 1488);
	AddElement(tree, 0);

	PrintTree(tree->Root, 1);
	DeleteElement(tree->Root, 1488);
	printf("\n\n\n");
	PrintTree(tree->Root, 1);

	Res_Search = 0;
	Res_Search = SearchElement(tree, 1488);

	if (Res_Search == -1)
		return;
	else if (Res_Search == 0)
		printf("Element in Tree\n");
	else
		printf("Element not in Tree\n");

	FreeTree(tree->Root);
	free(tree);
}