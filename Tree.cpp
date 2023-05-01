#include <iostream>
#include <queue>
#include <stack>

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
    
    void preorder()
    {
        Node* current = root;
        stack<Node*> s;        
        
        while(!s.empty() || current)
        {
            if(current)
            {
                s.push(current);    
                cout<< current->data << " ";
                current = current->left;                
            }
            else
            {
                current = s.top();
                s.pop();
                current = current->right;
            }
            
        }
    }
    
    void inorder()
    {
        Node* current = root;
        stack<Node*> s;        
        
        while(!s.empty() || current)
        {
            if(current)
            {
                s.push(current);      
                
                current = current->left;                
            }
            else
            {
                current = s.top();
                s.pop();      
                cout<< current->data << " ";
                current = current->right;
            }
            
        }
    }    
    
    void postorder(Node* root) {
        stack<Node*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            Node* temp = s1.top();
            s1.pop();
            s2.push(temp);
            if (temp->left != nullptr) {
                s1.push(temp->left);
            }
            if (temp->right != nullptr) {
                s1.push(temp->right);
            }
        }
        while (!s2.empty()) {
            Node* temp = s2.top();
            s2.pop();
            cout << temp->key << " ";
        }
    }
    
    
    void insertBST(int v)
    {
        Node* nn = new Node(v);        
        if(root == NULL)
        {
            root = nn;
        }
        else
        {
            Node *p, *c;
            p = c = root;
            while(c != NULL)
            {
                p = c;
                if(v > p->data)
                {
                    c = p->right;
                }
                else
                {
                    c = p->left;
                }
            }
            if( v > p->data)
            {
                p->right = nn;
            }
            else p->left = nn;        
        }
    }
    
    ~Tree()
    {
        delete root;
    }
};

int main() {
    
    Tree t;
    t.insertBST(8);
    t.insertBST(3);
    t.insertBST(10);
    t.insertBST(1);
    t.insertBST(6);
    t.insertBST(14);
    t.insertBST(4);
    t.insertBST(7);
    t.insertBST(13);    
    

    t.inorder(); 
    
    cout << endl;
    
    t.preorder();
 

    return 0;
}
