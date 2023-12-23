#include <iostream>

using namespace std;

struct BST{
private:
	struct node {
		int data;
		node* left = nullptr, * right = nullptr;
	};
	node* root = nullptr, * current = nullptr, * temp = nullptr, * currentTail = nullptr;

public:
	void insert(int data) {
		node* newnode = new node;
		newnode->data = data;

		if (root == nullptr)
		{
			root = newnode;
			return;
		}
		current = root;
		while (current)
		{
			if (data == current->data)
			{
				cout << "\nthis element already exist. NO duplicated allowed!\n";
				return;
			}

			if (data < current->data)
			{
				if (current->left == nullptr)
				{
					current->left = newnode;
					break;
				}
				current = current->left;
			}

			else
			{
				if (current->right == nullptr)
				{
					current->right = newnode;
					break;
				}
				current = current->right;
			}
		}
	}

	bool search(int data)
	{
		if (!root)
		{
			cout << "\nThis tree is empty!\n";
			return false;
		}

		current = root;
		
		while (current) {
			currentTail = current;

			if (data < current->data)
				current = current->left;
			else
				current = current->right;
			if (current && current->data == data)
			{
				return true;
			}
		}
		return false;
	}

	bool Delete(int data)
	{
		if (search(data))
		{
				re_link();
				cout<<endl<<data<<" deleted";
				return true;
		}
		else
		{
			cout << "\nThis element ("<<data<<") does not exist in this tree!\n";
			return false;
			}		
	}

	void pre_order()
	{
		if (root)
			pre_order(root);
		else
		{
			cout << "\nThis tree is empty!\n";
			return;
		}
	}

private:

	void re_link()
	{
		if (current == currentTail->left)
		{
			if (!current->left && !current->right)
			{
				currentTail->left = nullptr;
				delete current;
			}
			else if (current->left && !current->right)
			{
				currentTail->left = current->left;
				delete current;
			}
			else if (!current->left && current->right)
			{
				currentTail->left = current->right;
				delete current;
			}
			else
			{
				currentTail->left = current->right;
				temp = current->right;
				while (temp->left)
				{
					temp = temp->left;
				}
				temp->left = current->left;
				delete current;
			}
		}

		else
		{
			if (!current->left && !current->right)
			{
				currentTail->right = nullptr;
				delete current;
			}
			else if (current->left && !current->right)
			{
				currentTail->right = current->left;
				delete current;
			}
			else if (!current->left && current->right)
			{
				currentTail->right = current->right;
			}
			else
			{
				currentTail->right = current->right;
				temp = current->right;
				while (temp->left)
				{
					temp = temp->left;
				}
				temp->left = current->left;
				delete current;
			}
		}
	}

	void pre_order(node* Root)
	{
		if (Root)
		{
			cout << Root->data << "  ";
			pre_order(Root->left);
			pre_order(Root->right);
		}
	}
	
};

int main()
{
	BST tree;
	tree.insert(8);
	tree.insert(3);
	tree.insert(10);
	tree.insert(1);
	tree.insert(6);
	tree.insert(4);
	tree.insert(7);
	tree.insert(14);
	tree.insert(13);

cout<<"\nElement in this tree -> ";
	tree.pre_order();

	if (tree.search(6))
		cout << "\n6 found in this tree\n";
	else
		cout << "\n6 not found in this tree\n";

	if (tree.search(13))
		cout << "\n13 found in this tree\n";
	else
		cout << "\n13 not found in this tree\n";
			if (tree.search(100))
		cout << "\n100 found in this tree\n";
	else
		cout << "\n100 not found in this tree\n";

        if(tree.Delete(3))
        {
        cout << "\n";
	tree.pre_order();	
        }
	
	if(tree.Delete(7))
	{
	cout << "\n";
	tree.pre_order();	
        }
	
	if(tree.Delete(8))
	{
	cout << "\n";
	tree.pre_order();
        }



}

