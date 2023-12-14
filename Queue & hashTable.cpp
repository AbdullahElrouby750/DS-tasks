#include <iostream>

#define sz 10

using namespace std;

template <class type>
class arrayed_queue
{
private:
	int front, rear;
	type queue[sz];
public:
	arrayed_queue() : front(-1),rear(-1){}

	bool isempty()
	{
		return (front == -1);
	}

	bool isfull()
	{
		return ((rear + 1) % sz == front);
	}

	void enqueue(type data)
	{
		if (isempty())
		{
			front = rear = 0;
			queue[front] = data;
		}

		else if (isfull())
		{
			cout << "This queue is full!\n";
			return;
		}

		else
		{
			rear = (rear + 1) % sz;
			queue[rear] = data;
		}
	}

	void dequeue()
	{
		if (isempty())
		{
			cout << "This queue is already empty!\n";
			return;
		}

		else if (rear == front)
			rear = front = -1;

		else
			front = (front + 1) % sz;
		cout << "front deleted\n";
	}

	type Front()
	{
		if (isempty())
		{
			cout << "This queue is empty!\n";
			return NULL;
		}

		return queue[front];
	}

	type Rear()
	{
		if (isempty())
		{
			cout << "This queue is empty!\n";
			return NULL;
		}

		return queue[rear];
	}

	void display()
	{
		if (isempty())
		{
			cout << "This queue is empty!\n";
			return;
		}

		cout << "Element in this queue [";
		for (int i = front; i != rear; i = ((i + 1) % sz))
		{
			cout << queue[i] << " ";
		}
		cout << queue[rear] << " ]\n";

	}

	void clear()
	{
		front = rear = -1;
	}

	~arrayed_queue()
	{
		clear();
	}
};

template <class type>
class linked_Queue
{
private:
	struct node
	{
		type data;
		node* next;
	};
	node* front, * rear, * current, * temp;
public:
	linked_Queue() : front(NULL), rear(NULL), current(NULL), temp(NULL){}

	bool isEmpty()
	{
		return (front==NULL);
	}

	void enqueue(type item)
	{
		node* newnode = new node;
		newnode->data = item;
		newnode->next = NULL;
		if (isEmpty())
		{
			front = rear = newnode;
		}
		else
		{
			rear->next = newnode;
			rear = newnode;
		}
		cout << item << " pushed\n";
	}

	void dequeue()// normal delete // delete front // FIFO theory
	{
		if (isEmpty())
		{
			cout << "Empty queue!\n";
			return;
		}

		else if (front == rear)
		{
			delete front;
			front = rear = NULL;
		}

		else
		{
			temp = front;
			front = front->next;
			delete temp;
			temp = NULL;
			cout << "front deleted\n";
		}
	}

	type& getfront()//return element in the front
	{
		if(!isEmpty())
			return front->data;
		else
			cout << "This queue is empty!\n";
	}

	type& getrear()//return element at the end
	{
		if(!isEmpty())
			return rear->data;
		else
			cout << "This queue is empty!\n";
	}

	void display()
	{
		current = front;
		cout << "Elements in this queue [ ";
		while (current != NULL)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << "]\n";
	}

	void clear()
	{
		current = front;
		while (current != NULL)
		{
			temp = current;
			current = current->next;
			delete temp;
			temp = NULL;
		}
		front = rear = NULL;
	}

	~linked_Queue()
	{
		clear();
	}
};

template<class type>
class hash_table
{
private:
	struct node {
		type data;
		node* next;
	};
	node* chainHead[sz], * current;
	int key;
	
public:

	hash_table(){
		key = -1;
		current = NULL;
		for (int i = 0; i < sz; i++)
		{
			chainHead[i] = NULL;
		}
	}

	void insert(type data)
	{
		key = data % sz;

		node* newnode = new node;
		newnode->data = data;
		newnode->next = NULL;

		if (chainHead[key] == NULL)
		{
			chainHead[key] = newnode;
		}

		else
		{
			current = chainHead[key];
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = newnode;
		}

	}

	bool get(type data)
	{
		key = data % sz;

		if (chainHead[key] == NULL)
		{
			cout << "Element (" << data << ") not found!\n";
			return false;
		}

		else
		{
			current = chainHead[key];
			while (current != NULL && current->data!=data)
			{
				current = current->next;
			}

			if (current == NULL)
			{
				cout << "Element (" << data << ") not found!\n";
				return false;
			}

			else
			{
				cout << "Element (" << data << ") found\n";
				return true;
			}
		}
	}

	void display()
	{
		for (int i = 0; i < sz; i++)
		{
			cout << "key[" << i << "] -> ";
			current = chainHead[i];

			while (current!=NULL)
			{
				cout << current->data << " -> ";
				current = current->next;
			}
			cout <<"NULL\n";
		}
	}
};


void arrayed_queue_app()
{
	arrayed_queue<int> queue;
	queue.enqueue(2);
	queue.enqueue(5);
	queue.enqueue(7);

	queue.dequeue();

	queue.enqueue(3);
	queue.enqueue(1);
	queue.enqueue(9);
	queue.enqueue(10);
	queue.enqueue(4);
	queue.enqueue(6);

	queue.dequeue();

	queue.enqueue(2);
	queue.enqueue(1);

	if (queue.isfull())
		cout << "True\n";
	else
		cout << "False\n";
	queue.display();
}

void linked_queue_app()
{
	linked_Queue<int> queue;

	queue.enqueue(2);
	queue.enqueue(4);
	queue.enqueue(6);

	queue.dequeue();

	queue.display();
}

void hash_table_app()
{
	hash_table<int> table;

	table.insert(89);
	table.insert(18);
	table.insert(49);
	table.insert(58);
	table.insert(9);

	table.get(9);
	table.get(19);

	table.display();
}

int main()
{
	int choose = 0;

	while (true)
	{

		cout << "Hash table task >> 1\nQueue task >> 2\n\n";
		cout << "your choice :: ";
		cin >> choose;
		cout << endl;

		if (choose == 1)
		{
			hash_table_app();
			break;
		}
		else if (choose == 2)
		{

			while (true)
			{
				cout << "Linked Queue >> 1\nArrayed queue >> 2\n\n";
				cout << "your choice :: ";
				cin >> choose;
				cout << endl;

				if (choose == 1)
				{
					linked_queue_app();
					break;
				}

				else if (choose == 2)
				{
					arrayed_queue_app();
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