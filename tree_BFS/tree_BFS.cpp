#include <fstream>
#include <iostream>

using namespace std;

struct node
{
    int info;
    node* left;
    node* right;
};
typedef node* tinfo;

//17.7 з и е
//17.10-12
//

struct elem
{
    tinfo info;
    elem* next;
};

struct Queue
{
    int size;
    elem* first;
    elem* last;
};

Queue* create_queue()
{
    Queue* q = new Queue;
    q->first = new elem;
    q->first->next = NULL;
    q->last = q->first;
    q->size = 0;
    return q;
}

void enQueue(Queue* q, tinfo x)
{
    q->last->next = new elem;
    q->last = q->last->next;
    q->last->next = NULL;
    q->last->info = x;
    q->size++;
}

tinfo deQueue(Queue* q)
{
    elem* el = q->first;
    q->first = q->first->next;
    tinfo info = el->next->info;
    delete el;
    q->size--;
    return info;
}

bool isEmpty(Queue* q)
{
    return q->first == q->last;
}

node* create_node(int x)
{
    node* p = new node;
    p->info = x;
    p->left = NULL;
    p->right = NULL;

    return p;
}

void BFS(node* root)
{
    Queue* q = create_queue();
    node* p;
    enQueue(q, root);
    int cur = 1;
    int next = 0;
    while (!isEmpty(q))
    {
        p = deQueue(q);
        cur--;
        if (p->left)
        {
            enQueue(q, p->left);
            next++;
        }

        if (p->right)
        {
            enQueue(q, p->right);
            next++;
        }
        cout << p->info << ' ';
        if (cur == 0)
        {
            cout << endl;
            cur = next;
            next = 0;
        }
    }
}

int len_to_E(node* root, int E)
{
    int i = 0;
    Queue* q = create_queue();
    enQueue(q, root);
    node* p;
    int curr = 1;
    int next = 0;
    while (!isEmpty(q))
    {
        p = deQueue(q);
        curr--;
        if (p->info == E) return i;
        if (p->left)
        {
            enQueue(q, p->left);
            next++;
        }

        if (p->right)
        {
            enQueue(q, p->right);
            next++;
        }
        if (curr == 0)
        {
            curr = next;
            next = 0;
            i++;
        }
    }

    return -1;
}

int count_nodes_in_level(node* root, int level)
{
    Queue* q = create_queue();
    enQueue(q, root);
    node* p;
    int i = 0;
    int curr = 1;
    int next = 0;

    while (!isEmpty(q))
    {
        if (level == i) return curr;
        p = deQueue(q);
        curr--;
        if (p->left)
        {
            enQueue(q, p->left);
            next++;
        }
        if (p->right)
        {
            enQueue(q, p->right);
            next++;
        }
        
        if (curr == 0)
        {
            
            i++;
            curr = next;
            next = 0;
        }

    }
    return -1;
}

node* copy(node* root)
{
    node* root1 = NULL;

    Queue* q = create_queue();
    Queue* q1 = create_queue();
    enQueue(q, root);
    enQueue(q1, root1);
    node* p;
    node* p1;

    while (!isEmpty(q))
    {
        p = deQueue(q);
        p1 = deQueue(q1);
        p1 = create_node(p->info);
        if (p->left)
        {
            enQueue(q, p->left);
            enQueue(q1, p1->left);
        }
        if (p->right)
        {
            enQueue(q, p->right);
            enQueue(q1, p1->right);
        }
    }

    return root1;
}

node* create_tree(int n)
{
    node* root = create_node(1);
    int curr = 1;
    int next = 0;
    int i = 2;
    node* p;

    Queue* q = create_queue();
    enQueue(q, root);

    while (i != n)
    {
        p = deQueue(q);
        p->left = create_node(i);
        p->right = create_node(i);
        enQueue(q, p->left);
        enQueue(q, p->right);
        next += 2;
        curr--;
        if (curr == 0)
        {
            i++;
            curr = next;
            next = 0;
        }
        
    }

    return root;
}

bool has_two_similar(node* root)
{
    bool has_two = false;
    node* p;
    node* p1;

    Queue* q = create_queue();
    Queue* q1 = create_queue();

    enQueue(q, root);

    while (!isEmpty(q) && !has_two)
    {
        p = deQueue(q);
        
        if (p->left)
        {
            enQueue(q, p->left);
        }
        if (p->right)
        {
            enQueue(q, p->right);
        }
        enQueue(q1, root);
        while (!isEmpty(q1) && !has_two)
        {
            p1 = deQueue(q1);
            if (p1->info == p->info && p1 != p) has_two = true;
            if (p1->left) enQueue(q1, p1->left);
            if (p1->right) enQueue(q1, p1->right);
        }
    }
    return has_two;
}

node* search(node* root, int x)
{
    node* p = root;
    node* parent = NULL;

    while (p != NULL)
    {
        if (x > p->info)
        {
            parent = p;
            p = p->right;
        }
        else
        {
            parent = p;
            p = p->left;
        }
    }

    return parent;
}


void insert(node* &root, int x)
{
    node* p = root;

    Queue* q = create_queue();
    enQueue(q, root);

    while (!isEmpty(q) && p)
    {
        if (x >= p->info)
        {
            enQueue(q, p->right);
            if (!p->right) p->right = create_node(x);
        }  
        else
        {
            enQueue(q, p->left);
            if (!p->left) p->left = create_node(x);
        }
        
        p = deQueue(q);
    }
    if (p == NULL) p = create_node(x);
}

void remove(node* root, int x)
{
    node* parent = search(root, x);
    node* p;

    if (parent->left && parent->left->info == x)
    {
        if (parent->left->left == NULL && parent->left->right == NULL)
        {
            delete parent->left;
            parent->left = NULL;
        }
    }
    if (parent->right && parent->right->info == x)
    {
        if (parent->right->right == NULL && parent->right->left == NULL)
        {
            delete parent->right;
            parent->right = NULL;
        }
    }
}

int main()
{
    node* root = create_node(9);
    root->left = create_node(5);
    root->right = create_node(12);
    root->left->left = create_node(4);
    root->left->right = create_node(7);
    root->right->left = create_node(10);
    root->right->right = create_node(13);

    //BFS(root);

    //cout << len_to_E(root, 0) << endl;
    //cout << count_nodes_in_level(root, 2);

    //node* root1 = copy(root);
    //BFS(root1);

    //node* root1 = create_tree(5);
    //BFS(root1);

    //cout << has_two_similar(root);

    //node* el = search(root, 3);
    
    insert(root, 6);
    insert(root, 11);
    BFS(root);

}
