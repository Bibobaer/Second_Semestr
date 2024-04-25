#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Res_Search;

typedef struct TreeNode
{
	int data;
	struct TreeNode* RightBranch;
	struct TreeNode* LeftBranch;
}TreeNode;

TreeNode* Temple;

typedef struct BinaryTree {
	struct TreeNode* Root;
}BinaryTree;

TreeNode* CreateNode(int value);
BinaryTree* CreateTree();

void AddElement(BinaryTree* tree, int value);
int SearchElement(BinaryTree* tree, int value);
void PrintTree(TreeNode* tree, int level);
void FreeTree(TreeNode* tree);
TreeNode* minValue(TreeNode* tree);
TreeNode* DeleteElement(TreeNode* tree, int value);

void TestTree(BinaryTree* tree);