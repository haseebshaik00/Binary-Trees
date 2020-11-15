#include<iostream>
#include<queue>
using namespace std;

class BinaryTreeNode
{
public:
    int data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode(int d)
    {
        data=d;
        left=NULL;
        right=NULL;
    }
};

BinaryTreeNode* preorderBuild()
{
    int d;
    cin>>d;

    if(d==-1)
        return NULL;

    BinaryTreeNode *root = new BinaryTreeNode(d);
    root->left=preorderBuild();
    root->right=preorderBuild();
    return root;
}

void preorderPrint(BinaryTreeNode *root)
{
    if(root==NULL)
        return;
    cout<<root->data<<" ";
    preorderPrint(root->left);
    preorderPrint(root->right);
}

void postorderPrint(BinaryTreeNode *root)
{
    if(root==NULL)
        return;
    postorderPrint(root->left);
    postorderPrint(root->right);
    cout<<root->data<<" ";
}

void inorderPrint(BinaryTreeNode *root)
{
    if(root==NULL)
        return;
    inorderPrint(root->left);
    cout<<root->data<<" ";
    inorderPrint(root->right);
}

int BinaryTreeHeight(BinaryTreeNode *root)
{
    if(root==NULL)
        return 0;
    int left_height = BinaryTreeHeight(root->left);
    int right_height = BinaryTreeHeight(root->right);
    return max(left_height,right_height) + 1;
}

void printKthlevel(BinaryTreeNode *root, int k)
{
    if(root==NULL)
        return;
    if(k==1)
    {
        cout<<root->data<<" ";
        return;
    }
    printKthlevel(root->left,k-1);
    printKthlevel(root->right,k-1);
    return;
}

void levelorderPrint(BinaryTreeNode *root)
{
    int height = BinaryTreeHeight(root);
    cout<<"Level Order : ";
    for(int i=1;i<=height;i++)
        printKthlevel(root, i);
    cout<<endl;
}

void bfs(BinaryTreeNode *root)
{
    queue<BinaryTreeNode *> q;
    q.push(root);
    while(!q.empty())
    {
        BinaryTreeNode *f=q.front();
        q.pop();
        cout<<f->data<<" ";
        if(f->left)
            q.push(f->left);
        if(f->right)
            q.push(f->right);
    }
}

int main() {
    BinaryTreeNode* root = preorderBuild(); //Input : 3 4 -1 6 -1 -1 5 1 -1 -1 -1
    cout<<endl<<"Preorder : ";
    preorderPrint(root);    // Output : 3 4 6 5 1
    cout<<endl<<"Postorder : ";
    postorderPrint(root);   // Output : 6 4 1 5 3
    cout<<endl<<"Inorder : ";
    inorderPrint(root);     // Output : 4 6 3 1 5
    cout<<endl<<"Height of Binary Tree : "<<BinaryTreeHeight(root)<<endl;
    levelorderPrint(root);
    cout<<"BFS Traversal : ";
    bfs(root);
	return 0;
}
