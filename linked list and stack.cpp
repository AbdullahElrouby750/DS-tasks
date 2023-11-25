#include <iostream>
#include <string>

#define null NULL

using namespace std;

template <class type>
class ll
{
private:

	struct node {
		type data;
		node* next;
	};
	node* head, * current, * temp;

public:

	ll() : head(null), current(null), temp(null) {}

	bool isempty()
	{
		return head == null;
	}

	void insert(type value)
	{
		node* newnode = new node;
		newnode->data = value;
		newnode->next = null;

		if (isempty())
		{
			head = newnode;
			return;
		}

		current = head;
		while (current->next != null)
		{
			current = current->next;
		}

		current->next = newnode;
	}

	void traverse()
	{

		if (isempty())
		{
			cout << "This list is empty!\n";
			return;
		}

		current = head;

		cout << "| ";
		while (current != null)
		{
			cout << current->data << " | ";
			current = current->next;
		}
		cout << endl;
	}

	void delete_item(type value)
	{

		if (isempty())
		{
			cout << "list is already empty!!\n";
			return;
		}

		if (head->data == value)
		{
			delete head;
			head = null;
		}

		current = head;
		while (current->next->data != value)
		{
			current = current->next;
		}
		temp = current->next;
		current->next = temp->next;

		delete temp;
		temp = null;
	}

	void clear_list()
	{
		if (isempty())
			return;

		current = head;
			while (current != null)
			{
				head = head->next;
				delete current;
				current = head;
			}
	}

	~ll()
	{
		clear_list();
	}

};

template <class Type>
class linked_stack {
private:

	struct node {
		Type data;
		node* next;
	};
	node* top, * temp;

public:

	linked_stack() : top(null), temp(null) {}

	void push(Type value)
	{
		node* newnode = new node;
		newnode->data = value;
		newnode->next = null;

		if (isempty())
		{
			top = newnode;
		}

		else
		{
			newnode->next = top;
			top = newnode;
		}
	}

	void pop()
	{
		if (isempty())
		{
			cout << "This stack is empty!\n";
			return;
		}
		else if (top->next == null)
		{
			delete top;
			top = null;
		}

		else
		{
			temp = top;
			top = top->next;
			temp = null;
			delete temp;
		}
	}

	Type Top()
	{
		if (isempty())
		{
			cout << "this stack is empty!\n";
			return -1;
		}
		return top->data;
	}

	void display()
	{
		if (isempty())
		{
			cout << "This stack is empty!\n";
			return;
		}

		temp = top;
		while (temp != null)
		{
			cout << "|" << temp->data << "| \n";
			temp = temp->next;
		}
		cout << "----\n";

	}

	bool isempty()
	{
		return top == null;
	}

	void clear()
	{
		while (top != null)
		{
			temp = top;
			top = top->next;
			delete temp;
		}
		temp = null;
	}

	~linked_stack()
	{
		clear();
	}

};

#define sz 10
template <class type>
class arrayed_stack {
private:
	int top;
	type stack[sz];
public:
	arrayed_stack() {
		top = -1;
	}

	bool isempty()
	{
		return top == -1;
	}

	bool isfull()
	{
		return top == (sz - 1);
	}

	void push(type value)
	{
		if (isempty())
		{
			top = 0;
			stack[top] = value;
		}

		else if (isfull())
		{
			cout << "this stack is full!\n";
			return;
		}
		else
		{
			top++;
			stack[top] = value;
		}
	}

	void pop()
	{
		if (isempty())
		{
			cout << "this stack is empty!\n";
			return;
		}

		else
		{
			top--;
		}
	}

	type Top()
	{
		if (!isempty())
			return stack[top];
	}

	void display()
	{
		for (int i = top; i > -1; i--)
		{
			cout << "|" << stack[i] << "|" << endl;
		}
		cout << "----" << endl;
	}

	void clear_stack()
	{
		top = -1;
	}

	~arrayed_stack()
	{
		clear_stack();
	}
};

void linked_list_app()
{
	ll<int> linked_list;

	linked_list.insert(30);
	linked_list.insert(5);
	linked_list.insert(5);
	linked_list.insert(20);
	linked_list.insert(70);
	linked_list.insert(10);

	cout << "your list :: ";
	linked_list.traverse();

	linked_list.delete_item(20);

	cout << "your list :: ";
	linked_list.traverse();
}

void linked_stack_app()
{
	linked_stack<char> stack;
	string s;
	int choose = 0;

	while (true)
	{

		cout << "Revers a sentence >> 1\ncheck the balanced parentheses >> 2\n\n";
		cout << "your choice :: ";
		cin >> choose;
		cout << endl;

		if (choose == 1)
		{

			cin.ignore();
			cout << "Plz, enter the word :: ";
			s.clear();
			getline(cin, s);

			for (int i=0;i<s.size();i++)
			{
				stack.push(s[i]);
			}

			while (!stack.isempty())
			{
				cout << stack.Top();
				stack.pop();
			}
			break;
		}

		else if (choose == 2)
		{

			bool balanced = true;
			cin.ignore();
			stack.clear();
			s.clear();
			cout << "plz, enter the expression :: ";
			getline(cin, s);

			for (int i = 0; i < s.size(); i++)
			{
				if (s[i] == '(' || s[i] == '{' || s[i] == '[')
					stack.push(s[i]);
				if (s[i] == ')' || s[i] == '}' || s[i] == ']')
				{
					if (stack.isempty())
					{
						balanced = false;
						break;
					}
					else
					{
						if (s[i] == ')' && stack.Top() == '(')
							stack.pop();
						else if (s[i] == '}' && stack.Top() == '{')
							stack.pop();
						else if (s[i] == ']' && stack.Top() == '[')
							stack.pop();
						else
							balanced = false;
					}
				}
			}
			if (!stack.isempty())
				balanced = false;

			if (balanced == true)
				cout << "balanced\n";
			else
				cout << "not balanced\n";
			break;
		}

		else
		{
			cout << "Invalid choice!\nPLz, choose again.\n";
		}
	}

}

void arrayed_stack_app()
{
	arrayed_stack<int> stack;

	stack.push(2);
	stack.push(10);
	stack.push(5);

	stack.display();

	stack.pop();

	stack.push(7);
	stack.display();

	cout << stack.Top() << endl;

	if (stack.isempty())
		cout << "true\n";
	else
		cout << "false\n";
}

int main()
{
	int choose = 0;

	while (true)
	{

		cout << "Linked list task >> 1\nstack task >> 2\n\n";
		cout << "your choice :: ";
		cin >> choose;
		cout << endl;

		if (choose == 1)
		{
			linked_list_app();
			break;
		}
		else if (choose == 2)
		{

			while (true)
			{
				cout << "Linked stack >> 1\nArrayed stack >> 2\n\n";
				cout << "your choice :: ";
				cin >> choose;
				cout << endl;

				if (choose == 1)
				{
					linked_stack_app();
					break;
				}

				else if (choose == 2)
				{
					arrayed_stack_app();
					break;
				}

				else
				{
					cout << "Invalid choice!\nPLz, choose again.\n";
				}
			}

			break;
		}

		else
		{
			cout << "Invalid choice!\nPLz, choose again.\n";
		}
	}


}
