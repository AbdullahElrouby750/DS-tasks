#include <iostream>
#include <stack>
#include <cmath>
#include <string>

using namespace std;


class exp_tree {
private:
	struct node {
		string data =" ";
		node* left = nullptr, * right = nullptr, * parent = nullptr;
	};
	node* root, * current, * currentTail, * start;
	string exp;
	char ch;

public:

	exp_tree(string EXP) : root(nullptr),current(nullptr),currentTail(nullptr),exp(EXP),ch('\0') {}

	int expression()
	{
		set_to_tree();
		cout << "\nTree in pre order :: ";
		pre_order(root);
		cout << "\nTree in post order :: ";
		post_order(root);
		return solve();
	}

private:

	bool is_operator(char& ch)
	{
		return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')');
	}

	int set_weight(char& ch)
	{
		int weight = 0;
		switch (ch)
		{
		case '+':
		case '-':
			weight = 1;
			break;
		case '*':
		case '/':
			weight = 2;
			break;
		case '^':
			weight = 3;
			break;
		}
		return weight;
	}

	string infix_To_postfix()
	{
		

		stack<char> s;
		int weight1 = -1, weight2 = -1, temp_weight = -1;
		string postfix = "";

		for (char ch : exp)
		{
			if (is_operator(ch))
			{

				if (ch == '(')
				{
					s.push(ch);
					while (ch != ')')
					{
						ch++;
						if (is_operator(ch))
						{
							weight2 = set_weight(ch);
							if (weight2 > temp_weight)
							{
								s.push(ch);
								temp_weight = weight2;
							}

							else
							{
								while (weight2 <= temp_weight && !s.empty())
								{
									postfix = s.top();
									s.pop();
								}
								s.push(ch);
								temp_weight = weight2;
							}
						}
						else if(isalnum(ch))
							postfix += ch;
						else
						{
							cout << "ERROR! a non valid character (" << ch << endl;
							return NULL;
						}
					}
					while (s.top() != '(')
					{
						postfix += s.top();
						s.pop();
						if(!s.empty())
							temp_weight = set_weight(s.top());
					}
					temp_weight = -1;
				}

				else
				{
					weight2 = set_weight(ch);
					if (weight2 > weight1)
					{
						s.push(ch);
						weight1 = weight2;
					}
					else
					{
						while (weight2 <= weight1 && !s.empty())
						{
							postfix += s.top();
							s.pop();
							if(!s.empty())
								weight1 = set_weight(s.top());
						}
						s.push(ch);
						weight1 = weight2;
					}
				}
			}
			else if (isalnum(ch))
				postfix += ch;
			else
			{
				cout << "ERROR! a non valid character (" << ch << endl;
				return NULL;
			}
		}

		while (!s.empty())
		{
			postfix += s.top();
			s.pop();
		}
		return postfix;
	}

	void set_to_tree()
	{
		stack<char> s;

		exp = infix_To_postfix();

		for (char ch : exp)
		{
			if (is_operator(ch))
			{
				node* newnode = new node;
				newnode->data = ch;
				if (root == nullptr)
				{
					start = root = newnode;
					node* rightnode = new node;
					rightnode->data = s.top();
					rightnode->parent = root;
					s.pop();
					node* leftnode = new node;
					leftnode->data = s.top();
					leftnode->parent = root;
					s.pop();
					root->left = leftnode;
					root->right = rightnode;
				}
				else
				{
					node* rightnode = new node;
					rightnode->data = s.top();
					rightnode->parent = newnode;
					newnode->left = root;
					newnode->right = rightnode;
					root->parent = newnode;
					s.pop();
					root = newnode;
				}
			}
			else
				s.push(ch);
		}
	}

	int solve()
	{
		current = start;
		while (current)
		{
			switch (current->data[0])
			{
			case '+':
				current->data = to_string(stoi(current->left->data) + stoi(current->right->data));
				break;
			case '-':
				current->data = to_string(stoi(current->left->data) - stoi(current->right->data));
				break;
			case '*':
				current->data = to_string(stoi(current->left->data) * stoi(current->right->data));
				break;
			case '/':
				if (stoi(current->left->data) == 0)
				{
					cout << "\n ERROR! can't divide over a 0\n";
					return-1;
				}
				current->data = to_string(stoi(current->left->data) / stoi(current->right->data));
				break;
			case '^':
				current->data = to_string(pow(stoi(current->left->data), stoi(current->right->data)));
				break;
			}
			if (current->parent == nullptr)
				break;
			current = current->parent;
		}
		return stoi(current->data);
		
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

	void post_order(node* Root) //display tree in(left - right - root)
	{
		if (Root != NULL)
		{
			pre_order(Root->left);
			pre_order(Root->right);
			cout << Root->data << "  ";
		}
	}

};

int main()
{
	string exp;
	cout << "Plz, enter the expression : ";
	cin >> exp;

	exp_tree equ(exp);
	cout << "\nThe result :: " << equ.expression() << endl;
}