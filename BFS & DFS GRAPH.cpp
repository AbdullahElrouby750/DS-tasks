#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;


template<typename type>
class graph {

	struct node {
		type data;
		bool visited = false;
		node* adj[10] = {nullptr};
		//int index = -1;
	};
	node* first, * current,*old_node;
	unordered_map<type, node*> nodes;

public:
	graph() : first(nullptr),current(nullptr),old_node(nullptr) {}

	bool is_empty()
	{
		return first == nullptr;
	}

	void First(type data) // insert first element
	{
		if(is_empty())
		{
			node* newnode = new node;
			newnode->data = data;
			nodes[newnode->data] = newnode;
			first = newnode;
		}
		else
		{
			cout << "\nThis graph already have elements with first node = " << first->data << endl;
			return;
		}
	}

	void insert(type old_data,type new_data) //inset new element or link two existing elements
	{
		if(!is_empty())
		{
			if (nodes.find(new_data) != nodes.end())
			{
				node* temp = nodes.at(new_data);
				int i = 0;
				while (temp->adj[i])
				{
					try
					{
						old_node = nodes.at(old_data);
					}
					catch (const out_of_range& e)
					{
						cout << "\nThis node (" << old_data << ") does not exist!\n";
						return;
					}

					if (old_node == temp->adj[i])
					{
						cout << "\nThis element (" << new_data << ") already linked to ("<<old_data<<") !\n";
						return;
					}
					i++;
				}

				i = 0;
				while (temp->adj[i] && i < 10)
				{
					temp->adj[++i];
				}
				if (i == 10)
				{
					cout << "This node's adjs (" << new_data << ") are full\nchoose another node\n ";
					return;
				}

				int i1 = 0;
				while (old_node->adj[i1] && i1 < 10)
				{
					old_node->adj[++i1];
				}
				if (i1 == 10)
				{
					cout << "This node's adjs (" << old_data << ") are full\nchoose another node\n ";
					return;
				}

				old_node->adj[i1] = temp;
				temp->adj[i] = old_node;
				return;
			}
				node* newnode = new node;
				newnode->data = new_data;

				try
				{
					old_node = nodes.at(old_data);
				}
				catch (const out_of_range& e)
				{
					cout << "\nThis node (" << old_data << ") does not exist!\n";
					return;
				}

				int i = 0;
				while (old_node->adj[i] && i < 10)
				{
					old_node->adj[++i];
				}

				if (i == 10)
				{
					cout << "This node's adjs ("<<old_data<<") are full\nchoose another node\n ";
					return;
				}

				else
				{
					old_node->adj[i] = newnode;
					newnode->adj[0] = old_node;
					nodes[newnode->data] = newnode;
				}
		}

		else
		{
			cout << "\n this graph is empty!\nAdding (" << new_data << ") as a starting node\n";
			First(new_data);
		}

	}

	bool BFT(type start) //if false ask if want to keep going in the main
	{
		if (is_empty())
		{
			cout << "\nERROR! no graph exist!\n";
			return false;
		}
		try
		{
			current = nodes.at(start);
		}
		catch (const out_of_range& e)
		{
			cout << endl << e.what() << "\nThis node (" << start << ") does not exist!\nchoose another start\n";
			return false;
		}

		int i = 0;
		node* temp = nullptr;
		queue<node*> queue;

		queue.push(current);
		current->visited = true;

		while (!queue.empty())
		{
			while (current->adj[i])
			{
				temp = current->adj[i++];
				if (temp->visited == true)
					continue;
				queue.push(temp);
				temp->visited = true;
			}
			i = 0;
			cout << current->data << "  ";
			queue.pop();
			if(!queue.empty())
				current = queue.front();
		}

		for (auto n : nodes)
		{
			temp = n.second;
			temp->visited = false;
		}

	}

	bool DFT(type start)
	{
		if (is_empty())
		{
			cout << "\nERROR! no graph exist!\n";
			return false;
		}
		try
		{
			current = nodes.at(start);
		}
		catch (const out_of_range& e)
		{
			cout << endl << e.what() << "\nThis node (" << start << ") does not exist!\nchoose another start\n";
			return false;
		}

		int i = 0;
		node* temp = nullptr,*temp2=nullptr;
		stack<node*> stack;

		stack.push(current);
		

		while (!stack.empty())
		{
			cout << current->data << "  ";
			current->visited = true;
			temp2 = current->adj[0];
			if (temp2->visited == true)
			{
				i = 0;
				while (current->adj[i])
				{
					temp = current->adj[i++];
					if (temp->visited == false)
					{
						stack.push(temp);
						current = temp;
						break;
					}

					else if (current->adj[i] == nullptr)
					{
						if(!stack.empty())
						{
							stack.pop();
							if(!stack.empty())
								current = stack.top();
							i = 0;
						}
					}
				}
			}
			else
			{
				current = current->adj[0];
				stack.push(current);
			}
		}

		for (auto n : nodes)
		{
			temp = n.second;
			temp->visited = false;
		}
	}
};
int main()
{
	graph<int> g;

	g.First(1);//insert first node

	g.insert(1, 2);
	g.insert(1, 3);
	g.insert(1, 5);
	g.insert(2, 5);
	g.insert(6, 2);
	g.insert(3, 6);
	g.insert(3, 4);
	g.insert(1, 4);
	g.insert(1, 2);

	cout << "\n\nGraph with BFT -> ";
	g.BFT(1);

	cout << "\n\nGraph with DFT -> ";
	g.DFT(1);
	
	return 0;
}
