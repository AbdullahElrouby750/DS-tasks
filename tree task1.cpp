#include <iostream>
#include <queue>

using namespace std;


struct node {
	int data;
	node* left = nullptr, * right = nullptr;
};
struct tree {
private:

	node* root = nullptr, * current = nullptr;

public:

	node* insert(int data)
	{
		node* newnode = new node;
		newnode->data = data;
		return newnode;
	}

	void pre_order(node* Root) //display tree in(root - left - right)
	{
		if (Root != NULL)
		{
			cout << Root->data << "  ";
			pre_order(Root->left);
			pre_order(Root->right);
		}
	}

	void in_order(node* Root) //display tree in(left - root - right)
	{
		if (Root != NULL)
		{
			pre_order(Root->left);
			cout << Root->data << "  ";
			pre_order(Root->right);
		}
	}

	void post_order(node* Root) //display tree in(left - right - root)
	{
		if (Root != NULL)
		{
			pre_order(Root->left);
			pre_order(Root->right);
			cout << Root->data << "  ";
		}
	}

	void level_order(node* Root)
	{
		queue<node*> q;
		q.push(Root);

		while (!q.empty())
		{
			current = q.front();
			cout << current->data << "  ";
			q.pop();

			if (current->left)
				q.push(current->left);
			if (current->right)
				q.push(current->right);
		}
	}

};

int main()
{
	tree t;
	node* root = nullptr;
	root = t.insert(1);
	root->left = t.insert(2);
	root->right = t.insert(3);
	root->left->left = t.insert(4);
	root->left->right = t.insert(5);
	root->left->right->left = t.insert(7);
	root->left->right->right = t.insert(8);
	root->right->right = t.insert(6);
	root->right->right->left = t.insert(9);

	cout << "\nlevel order traversing\n";
	t.level_order(root);

	cout << "\nin-order traversing\n";
	t.in_order(root);

	cout << "\npre-order traversing\n";
	t.pre_order(root);

	cout << "\npost-order traversing\n";
	t.post_order(root);
}