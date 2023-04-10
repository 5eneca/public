#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int _data_)
    {
        data = _data_;
        left = NULL;
        right = NULL;
    }
};

struct Tree
{
    Node* root;

    Tree() : root(NULL) {}

    void push(int data)
    {        
        Node* newNode = new Node(data);
    
        if(root == NULL)
        {
            root = newNode;
            return;
        }        
        
        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* current = q.front();
            q.pop();

            if (current->left == NULL)
            {
                current->left = newNode;
                return;
            }
            else if (current->right == NULL)
            {
                current->right = newNode;
                return;
            }

            q.push(current->left);
            q.push(current->right);
        }
        delete newNode;
    }

    void print(Node* root)
    {
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty())
        {
            Node* curr = q.front();
            q.pop();
            
            cout << curr->data << " ";
            
            if (curr->left != NULL) q.push(curr->left);
            if (curr->right != NULL) q.push(curr->right);
        }
    }
    
    void print()
    {
        print(root);
    }
    
    ~Tree()
    {
        delete root;
    }
};

int main() {
    
    Tree t;
    
    t.push(45);
    t.push(55);
    t.push(667);
    t.push(71);
    t.push(675);
    t.push(75);
    t.push(111);

    t.print();
    
    cout << endl;

    return 0;
}
