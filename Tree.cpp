#include <iostream>
using namespace std;

template <typename K> struct Node
{  
    K data;
    Node<K>* prevAddress;
    Node<K>* nextAddress;
    Node()
    {
        nextAddress = NULL;
        prevAddress = NULL;
    }    
};

template <typename T> struct DoublyLinkedList
{
    Node<T>* head;
    Node<T>* tail;
    DoublyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    
    bool isEmpty()
    {
        if(head == NULL && tail == NULL) return true;
        return false;
    }
    
    void insert(T v)
    {
        Node<T>* nn = new Node<T>();
        nn->data = v;
        if(head == NULL)
        {
            head = nn;
            tail = nn;
        }
        else
        {
            tail->nextAddress = nn;
            nn->prevAddress = tail;
            tail = nn;
        }
    }
    
    void insertAfter(T exval, T v)
    {
        Node<T>* left = head;
        Node<T>* right;
        while(left != NULL){
            if(left->data == exval ) break;
            left = left->nextAddress;
        }
        if(left != NULL)
        {
            Node<T>* nn = new Node<T>();
            //new node operations
            nn->data = v;
            nn->prevAddress = left;
            nn->nextAddress = left->nextAddress;

            //fix left node
            left->nextAddress = nn;

            //fix right node
            if(left->nextAddress == NULL) right = NULL;
            else
            {
                right = left->nextAddress;
                right->prevAddress = nn;
            }

        }
        else insert(v);
    }

    void InsertAtFirst(T v)
    {
        Node<T>* temp = new Node<T>();
        temp->data = v;
        temp->nextAddress = head;
        head->prevAddress = temp;
        head = temp;
    }
    
    void DeleteFirst()
    {
        head = head->nextAddress;
    }
    
    void Delete(T v)
    {
        Node<T>* temp = head;
        Node<T>* previousNode = head;
        Node<T>* right;

        if(temp->data == v)
        {
            head = head->nextAddress;
            head->prevAddress = NULL;
        }
        else
        {
            while(temp->data != v)
            {
                if(temp == tail) return;
                previousNode = previousNode->nextAddress;
                temp = previousNode->nextAddress;
            }
            if(temp->nextAddress == NULL)
            {
                previousNode->nextAddress = NULL;
            }
            else
            {
                right = temp->nextAddress;
                right->prevAddress = previousNode;
                previousNode->nextAddress = right;
            }
        }
    }

    void traverse()
    {
        Node<T>* temp = head;
        while(temp !=NULL){
            cout<< temp->data <<" ";
            temp = temp->nextAddress;
        }
        cout << endl;
    }

    Node<T>* getNode(T v)
    {
        Node<T>* temp = head;
        while(temp != NULL)
        {
            if(temp->data == v) return temp;
            temp = temp->nextAddress;
        }
        return NULL;
    }

};

template <typename J> struct LinkedQueue
{
    DoublyLinkedList<J> dll;
    
    bool isEmpty()
    {
        return dll.isEmpty();
    }
        
    void enqueue(J v)
    {
        dll.insert(v);
    }
    
    void dequeue()
    {
        dll.DeleteFirst();
    }

    J getFirstItem()
    {
        return dll.head->data;
    }
    
    void traverse()
    {
        if(!dll.isEmpty())
        {
            dll.traverse();
        }
    }
};

struct Tree
{
    LinkedQueue<Node<int>*> lq;
    
    void push(int v)
    {
        Node<int>* newNode = new Node<int>();
        newNode->data = v;
        if(lq.isEmpty())
        {
            lq.enqueue(newNode);
        }
        else
        {
            Node<int>* current = lq.getFirstItem();
            if(current->prevAddress)
            {
                current->prevAddress = newNode;
                lq.enqueue(newNode);
            }
            else if(current->nextAddress)
            {
                current->nextAddress = newNode;
                lq.enqueue(newNode);
            }
            else
            {
                lq.dequeue();
                push(v);
            }
        }        
        delete newNode;
    }
};


int main()
{
	

	return 0;
}
