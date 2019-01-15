#include<bits/stdc++.h>
using namespace std;

struct Node
{
    struct Node *left,*right;
    int data;
};

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void InsertNode(Node **root,int data)
{
    Node *newNode = createNode(data);
    if(*root == NULL)
    {
        *root = newNode;
        return;
    }
    Node *curr = *root;
    Node *prev = NULL;
    bool rflag = false;
    while(curr !=NULL)
    {
        prev= curr;
        if(data > curr->data)
        {
            rflag = true;
            curr = curr->right;
        }
        else
        {
            rflag = false;
            curr = curr->left;
        }
    }
    if(rflag)
        prev->right = newNode;
    else
        prev->left = newNode;
}

void inorder(Node *root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

void preorder(Node *root)
{
    if(root == NULL)
        return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root)
{
    if(root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

void preorderWihoutRecursion(Node *root)
{
    if(root == NULL)
        return;
    stack<Node *> S;
    S.push(root);
    while(!S.empty())
    {
        Node *curr = S.top();
        S.pop();
        cout<<curr->data<<" ";
        if(curr->right)
            S.push(curr->right);
        if(curr->left)
         S.push(curr->left);
    }
}

void postorderWithoutRecursionTwoStack(Node *root)
{
    if(root == NULL)
        return;
    stack<Node *> S1,S2;
    S1.push(root);
    while(!S1.empty())
    {
        Node *curr = S1.top();
        S1.pop();
        S2.push(curr);
        if(curr->left)
            S1.push(curr->left);
        if(curr->right)
            S1.push(curr->right);
    }
    while(!S2.empty())
    {
        Node *curr = S2.top();
        S2.pop();
        cout<<curr->data<<" ";
    }
}

void postorderWithoutRecursionOneStack(Node *root)
{
    if(root == NULL)
        return;
    stack<Node *> S;
    while(true)
    {
         while(root != NULL)
         {
             S.push(root);
             S.push(root);
             root = root->left;
         }
         if(S.empty())
            return;
         root = S.top();
         S.pop();
         if(!S.empty() && S.top() == root)
         {
             root = root->right;
         }
         else
         {
             cout<<root->data<<" ";
             root = NULL;
         }

    }
}

void inorderWithoutRecursion(Node *root)
{
    if(root == NULL)
        return;
    stack<Node *> S;
    while(!S.empty() || root != NULL)
    {
        while(root != NULL)
        {
            S.push(root);
            root = root->left;
        }
        root = S.top();
        S.pop();
        cout<<root->data<<" ";

        root = root->right;
    }
}

void inorderWithoutStack(Node *root)
{
    if(root == NULL)
        return;
    while(root != NULL)
    {
        if(root->left == NULL)
        {
            cout<<root->data<<" ";
            root = root->right;
        }
        else
        {
            Node *prev = root->left;
            while(prev->right != NULL && prev->right != root)
                prev = prev->right;
            if(prev->right == NULL)
            {
                prev->right = root;
                root = root->left;
            }
            else
            {
                prev->right = NULL;
                cout<<root->data<<" ";
                root = root->right;
            }
        }
    }
}

int searchIndex(int arr[],int low,int high,int data)
{
    for(int i = low;i<=high;i++)
    {
        if(data == arr[i])
            return i;
    }
}

Node *createTreeUtil(int in[], int pre[], int& preindex, int low, int high)
{
    if(low>high)
        return NULL;

    Node *root = createNode(pre[preindex++]);

    if(low == high)
        return root;
    int index = searchIndex(in,low,high,root->data);
    root->left = createTreeUtil(in,pre,preindex,low,index-1);
    root->right = createTreeUtil(in,pre,preindex,index+1,high);
    return root;
}

Node *createTree(int in[], int pre[], int N)
{
    if(N <= 0 )
        return NULL;
    int preindex = 0;
    Node *root = createTreeUtil(in,pre,preindex,0,N-1);
    return root;
}

int main()
{
    cout<<"Tree Traversal:"<<endl;
    Node *root = NULL;
    int arr[] = {10,6,15,4,8,12,18,5,14,20};
    int in[] = {4,5,6,8,10,12,14,15,15,18,20};
    int post[] = {};
    int pre[] = {10,6,4,5,8,15,12,14,18,20};
    int n = sizeof(arr) / sizeof(arr[0]);
    for(int i=0;i<n;i++)
    {
        InsertNode(&root,arr[i]);
    }
    Node *root1 = createTree(in,pre,10);
    cout<<"INORDER:"<<endl;
    inorder(root);
    cout<<endl;
    inorderWithoutRecursion(root1);
    cout<<endl;
    inorderWithoutStack(root);
    cout<<endl<<"PREORDER:"<<endl;
    preorder(root);
    cout<<endl;
    preorderWihoutRecursion(root1);
    cout<<endl<<"POSTORDER:"<<endl;
    postorder(root);
    cout<<endl;
    postorderWithoutRecursionTwoStack(root);
    cout<<endl;
    postorderWithoutRecursionOneStack(root1);
    return 0;
}
