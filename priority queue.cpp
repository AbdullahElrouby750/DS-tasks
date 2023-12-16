
#include <iostream>

#define null NULL

using namespace std;

template<class type>
struct priorty_queue {
private:
    struct node {
        type data;
        node* next,* pre;
        int priority=-1;//starting from 0
    };
    node* front=null, * rear=null, * current=null;
public:

    bool isempty()
    {
        return front == null;
    }

    void enqueue(type data, int priority) //takes data and it's priority
    {
        node* newnode = new node;
        newnode->data = data;
        newnode->priority = priority;
        newnode->next=newnode->pre = null;

        if (isempty())
        {
            front = rear = newnode;
        }

        else // search for the right place // work like a linked list in searching // each priority has a order like a queue
        {
            if (priority > front->priority) // if the new data has a higher priority, put it in the front of the queue.
            {
                newnode->next = front;
                front = newnode;
            }

            else if (priority <= rear->priority)// if the new data have a less priority than the rear(least priority in the queue), put it as a rear.
            {
                rear->next = newnode;
                newnode->pre = rear;
                rear = newnode;
            }

            else // if the new data has a priority that already exist in the queue, search for that priority and insert the data in it's right place (at the end of this priority groub not at the end of the queue)
            {
                current = front;
                while (current->next->priority >= priority) //update: don't need to check if current.next = null, as this else won't happen anyway if priority is <= least priority.
                    current = current->next;
                newnode->next = current->next;
                newnode->pre = current;
                current->next = newnode;
            }
        }
    }

    void dequeueMax() // delete first element with high priority (front)
    {
        if (isempty())
        {
            cout << "This queue is already empty!\n";
            return;
        }

        else if (front == rear)
        {
            delete front;
            front = rear = null;
        }

        else
        {
            current = front;
            front = front->next;
            front->pre = null;
            delete current;
        }
    }

    void dequeueMin() // delete last element with least priority (rear)
    {
        if (isempty())
        {
            cout << "This queue is already empty!\n";
            return;
        }

        else if (front == rear)
        {
            delete front;
            front = rear = null;
        }

        else
        {
            current = rear;
            rear = rear->pre;
            rear->next = null;
            delete current;
        }
    }

    type Front()
    {
        if (isempty())
            return null;
        else
            return front->data;
    }

    type Rear()
    {
        if (isempty())
            return null;
        else
            return rear->data;
    }

    void Priority(type data) // find the priority for every (data) 
    {
        if (isempty())
        {
            cout << "this queue is empty!\n";
            return;
        }

        current = front;
        bool found = false;
        while (current)
        {
            if (current->data == data)
            {
                found = true;
                cout << data << " found with priority number (" << current->priority << ")\n";
            }
            current = current->next;
        }
        if (found == false)
            cout << data << " is not in this queue!\n";

    }

    void display()
    {
        if (isempty())
        {
            cout << "This queue is empty!\n";
            return;
        }

        current = front;
        cout << "priority number (" << front->priority << ")\n";

        while (current)
        {
            cout << " " << current->data << " ";
            if ((current->next) && (current->priority != current->next->priority))
                cout << "\npriority number (" << current->next->priority << ")\n";
            current = current->next;
        }
        cout << endl;
    }

    void clear()
    {
        if (isempty())
        {
            cout << "this list is already empty!\n";
            return;
        }

        node* temp;
        current = front;

        while (current)
        {
            temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main()
{
    priorty_queue<int> queue;

    queue.enqueue(10,0);
    queue.enqueue(20,0);
    queue.enqueue(30,1);
    queue.enqueue(10,1);
    queue.enqueue(1,2);
    queue.enqueue(55,0);
    queue.enqueue(0,2);
    queue.enqueue(12,3);

    queue.Priority(20);
    queue.Priority(10);

    queue.display();

    queue.dequeueMax();
    queue.dequeueMax();
    queue.dequeueMin();

    cout << "Front (max priority) element is (" << queue.Front() << ")\n";
    cout << "Rear (min priority) element is (" << queue.Rear() << ")\n";

    queue.display();
}

