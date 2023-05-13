#include <iostream>
using namespace std;

struct queue
{
private:
	static const int size = 5;
	int values[size];
	int f, r;

public:
	queue() : f(-1), r(-1) {}

	bool isEmpty()
	{
		if(f == -1 && r == -1) return true;
		return false;
	}
	bool isFull()
	{
		if((r+1) % size == f) return true;
		return false;
	}
	void enqueue(int v)
	{
		if(isFull()) cout << "Queue is full!" << endl;
		else
		{
			if(isEmpty()) f = r = 0;
			else r = (r + 1) % size;
			values[r] = v;
		}
	}
	void dequeue()
	{
		if(f == r) { f = r = -1; }
		else if(isEmpty()) cout << "Queue is empty!" << endl;
		else
		{
			f = (f + 1) % size;
		}
	}
	int FrontValue()
	{
		if(!isEmpty()) return values[f];
		return -1;
	}
	void print()
	{
 		if(isEmpty()) cout << "Empty queue";
		else
		{
			if(f < r) for(int i = f; i <= r; i++) cout << values[i] << " ";
			else
			{
				for(int i = f; i < size; i++) cout << values[i] << " ";
				for(int i = 0; i <= r; i++) cout << values[i] << " ";
			}
		}
		cout << endl;
	}
};

int main()
{
	queue q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	q.print();

	q.dequeue();
	q.enqueue(99);

	q.print();

	return 0;
}
