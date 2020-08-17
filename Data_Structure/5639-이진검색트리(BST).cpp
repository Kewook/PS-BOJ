/*
트리 객체를 생성할때 new를 통해 생성하지 않으면 동적할당이 되지 않아 스택영역에만 올라가게 된다.
따라서 범위를 벗어나면 그 값이 사라지게 된다.
*/
#include<iostream>

using namespace std;

struct Tree {
	Tree *left, *right;
	int val;
	
	Tree(const int ipt) : left(NULL), right(NULL), val(ipt){}
};

Tree* insert(Tree *root, Tree *node) {
	if (root == NULL) return node;
	if (root->val > node->val)root->left = insert(root->left, node);
	else if(root->val < node->val)root->right = insert(root->right, node);
	
	return root;
}

void postorder(Tree *node) {
	if (node->left != NULL)postorder(node->left);
	if (node->right != NULL)postorder(node->right);
	cout << node->val << " ";
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
	
	Tree *tree = NULL;

	int node;
	while (true) {
		cin >> node;
		if (cin.fail())break;

		Tree *nnode = new Tree(node);
		tree = insert(tree, nnode);
	}

	postorder(tree);
	return 0;
}