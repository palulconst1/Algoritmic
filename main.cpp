#include <bits/stdc++.h>
using namespace std;

class node
{
    public:
    int key;
    node *left, *right;
};

node* newNode(int key)
{
    node* Node = new node();
    Node->key = key;
    Node->left = Node->right = NULL;
    return (Node);
}

node *rightRotate(node *x)
{
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

node *leftRotate(node *x)
{
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

node *splay(node *root, int key)
{
    if (root == NULL || root->key == key)
        return root;
    if (root->key > key)
    {
        if (root->left == NULL) return root;
        if (root->left->key > key)
        {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->key < key)
        {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL)? root: rightRotate(root);
    }
    else
    {
        if (root->right == NULL) return root;
        if (root->right->key > key)
        {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)
        {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL)? root: leftRotate(root);
    }
}
node *search(node *root, int key)
{
    return splay(root, key);
}
void preOrder(node *root)
{
    if (root != NULL)
    {
        cout<<root->key<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

node *insert(node *root, int k)
{
    if (root == NULL) return newNode(k);
    root = splay(root, k);
    node *newnode = newNode(k);
    if (root->key > k)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }

    return newnode;
}

struct node* delete_key(struct node *root, int key)
{
    struct node *temp;
    if (!root)
        return NULL;
    root = splay(root, key);
    if (key != root->key)
        return root;
    if (!root->left)
    {
        temp = root;
        root = root->right;
    }
    else
    {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }
    free(temp);
    return root;

}

int findMax(node* root)
{
    if (root == NULL)
    return 0;
    int res = root->key;
    int lres = findMax(root->left);
    int rres = findMax(root->right);
    if (lres > res)
    res = lres;
    if (rres > res)
    res = rres;
    return res;
}

int findmn(node* root)
{
    if(root->left==NULL)
        return root->key;
    return(findmn(root->left));
}

int findMin(node*root)
{
    int x=findMax(root);
    root=search(root, x);
    int y= findmn(root);
    return y;

}

int suc(node *root, int x)
{
    if((root->key<=x) && (root->right!=NULL))
        return(suc(root->right, x));
    else
        if(root->left!=NULL)
        return(suc(root->left, x));
    return root->key;
}

int succesor(node *root, int x)
{
    root=search(root, x);
    if (root->key==x)
        return x;
    if (findMax(root)<x)
        return -1;
    int y=suc(root, x);
    int z=root->key;
    if(y<x)
        return z;
    if(z>x&&z<y)
        return z;
    return y;
}

int pred(node *root, int x)
{
        if((root->key>=x) && (root->left!=NULL))
        return(suc(root->left, x));
    else
        if(root->right!=NULL)
        return(suc(root->right, x));
    return root->key;
}

int predecesor(node *root, int x)
{
    root=search(root, x);
    if (root->key==x)
        return x;
        if (findMin(root)>x)
        return -1;
    int y=pred(root->left, x);
    int z=root->key;
    if(z<x&&z>=y)
        return z;
        if(z<x&&z>y)
        return z;
    return y;
}

void interv(node *root, int x, int y)
{
    if (root != NULL)
        if(root->key>x && root->key<y)
    {
        cout<<root->key<<" ";
        interv(root->left, x, y);
        interv(root->right, x, y);
    }
}

ifstream fin ("date.in");

int nrop, op, val, val2;

int main()
{
    int a, b;
    fin>>nrop;
    fin>>a>>b;
    node *root = newNode(b);
    nrop--;
    while(nrop)
    {
        fin>>op;
        fin>>val;
switch (op) {
  case 1:
    {root = insert(root, val);
    break;}
  case 2:
      {int nr=0;
      root=search(root, val);
    while(root->key==val)
    {
    root=delete_key(root, val);
    nr++;
   root=search(root, val);}
   cout<<"Am sters "<<nr<<" de "<<val<<endl;
    break;}
  case 3:
      { root=search(root, val);
      if(root->key==val)
        cout<<1<<" Gasit"<<endl;
      else
        cout<<0<<" Negasit"<<endl;
    break;}
    case 4:
    {
        cout<<succesor(root, val);
        cout<<endl;
    break;}
    case 5:
    {
        cout<<predecesor(root, val);
        cout<<endl;
    break;}
  case 6:
    {
        fin>>val2;
        interv(root, val, val2);
        cout<<endl;
    break;}
    }
        nrop--;
    }
}
