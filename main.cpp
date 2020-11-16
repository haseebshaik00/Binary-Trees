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

class PairDiameter{
    public:
        int height;
        int diameter;
};

class PairHeightBalance{
    public:
        int height;
        bool balance;
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
    q.push(NULL);
    while(!q.empty())
    {
        BinaryTreeNode *f=q.front();
        if(f==NULL)
        {
            cout<<endl;
            q.pop();
            if(!q.empty())
                q.push(NULL);
        }
        else
        {
            q.pop();
            cout<<f->data<<" ";
            if(f->left)
                q.push(f->left);
            if(f->right)
                q.push(f->right);
        }
    }
}

int nodeCount(BinaryTreeNode *root)
{
    if(root==NULL)
        return 0;
    return 1 + nodeCount(root->left) + nodeCount(root->right);
}

int nodeSum(BinaryTreeNode *root)
{
    if(root==NULL)
        return 0;
    return root->data + nodeSum(root->left) + nodeSum(root->right);
}

int diameter(BinaryTreeNode *root)
{
    if(root==NULL)
        return 0;
    int h1 = BinaryTreeHeight(root->left);
    int h2 = BinaryTreeHeight(root->right);
    int op1 = h1+h2;
    int op2 = diameter(root->left);
    int op3 = diameter(root->right);
    return max(op1,max(op2,op3));
}

PairDiameter fastDiameter(BinaryTreeNode *root){
    PairDiameter p;
    if(root==NULL){
        p.diameter = p.height = 0;
        return p;
    }
    PairDiameter left = fastDiameter(root->left);
    PairDiameter right = fastDiameter(root->right);
    p.height = max(left.height,right.height) + 1;
    p.diameter = max(left.height+right.height, max(left.diameter,right.diameter));
    return p;
}

int sumReplacement(BinaryTreeNode *root)
{
    if(root==NULL)
        return 0;
    if(root->left == NULL && root->right == NULL)
        return root->data;
    int left = sumReplacement(root->left);
    int right = sumReplacement(root->right);
    int temp = root->data;
    root->data = left + right;
    return temp + root->data;
}

PairHeightBalance isHeightBalanced(BinaryTreeNode *root)
{
    PairHeightBalance p;
    if(root==NULL){
        p.height = 0;
        p.balance = true;
        return p;
    }
    PairHeightBalance left = isHeightBalanced(root->left);
    PairHeightBalance right = isHeightBalanced(root->right);
    p.height = max(left.height,right.height) + 1;
    if(abs(left.height-right.height)<=1 && left.balance && right.balance)
        p.balance = true;
    else
        p.balance = false;
    return p;
}

BinaryTreeNode *buildbbtreeFromArray(int a[],int s,int e)
{
    if(s>e)
        return NULL;
    int mid = (s+e)/2;
    BinaryTreeNode *root = new BinaryTreeNode(a[mid]);
    root->left = buildbbtreeFromArray(a,s,mid-1);
    root->right = buildbbtreeFromArray(a,mid+1,e);
    return root;
}

BinaryTreeNode * treeFromPreIn(int in[],int pre[],int s,int e)
{
    static int i = 0;   // static cz when the recursion comes back the variable will backtrack and we don't want that
    if(s>e)
        return NULL;
    BinaryTreeNode *root  = new BinaryTreeNode(pre[i]);
    int index = -1;
    for(int j=s;j<=e;j++)
    {
        if(in[j]==pre[i])
        {
            index=j;
            break;
        }
    }
    i++;
    root->left  = treeFromPreIn(in,pre,s,index-1);
    root->right = treeFromPreIn(in,pre,index+1,e);
    return root;
}

void mirror(BinaryTreeNode *root)
{
    if(root==NULL)
        return;
    mirror(root->left);
    mirror(root->right);
    swap(root->left,root->right);
}

void rightView(BinaryTreeNode *root, int level, int &maxlevel)
{
    if(root==NULL)
        return;
    if(level>maxlevel)
    {
        maxlevel=level;
        cout<<root->data<<" ";
    }
    rightView(root->right,level+1,maxlevel);
    rightView(root->left,level+1,maxlevel);
}

int main() {
    BinaryTreeNode* root = preorderBuild(); //Input : 3 4 -1 6 -1 -1 5 1 -1 -1 -1 or 8 10 1 -1 -1 6 9 -1 -1 7 -1 -1 3 -1 14 13 -1 -1 -1
    cout<<endl<<"Preorder : ";
    preorderPrint(root);    // Output : 3 4 6 5 1
    cout<<endl<<"Postorder : ";
    postorderPrint(root);   // Output : 6 4 1 5 3
    cout<<endl<<"Inorder : ";
    inorderPrint(root);     // Output : 4 6 3 1 5
    cout<<endl<<"Height of Binary Tree : "<<BinaryTreeHeight(root)<<endl;
    levelorderPrint(root);
    cout<<"BFS Traversal : "<<endl;
    bfs(root);
    cout<<"No. of Nodes : "<<nodeCount(root)<<endl;
    cout<<"Sum of Nodes : "<<nodeSum(root)<<endl;
    cout<<"Diameter of Nodes : "<<diameter(root)<<endl;
    PairDiameter p = fastDiameter(root);
    cout<<"Optimized Height : "<<p.height<<endl;
    cout<<"Optimized Diameter : "<<p.diameter<<endl;
	sumReplacement(root);
	cout<<"After Sum Replacement : ";
	preorderPrint(root);
	cout<<endl;
	if(isHeightBalanced(root).balance)
        cout<<"Balanced";
    else
        cout<<"Not a Balanced Tree"<<endl;
    int a[]={3,2,5,6,3,7,8,3};
    BinaryTreeNode *root1 = buildbbtreeFromArray(a,0,7);
    cout<<"Height Balanced Binary Tree From Array : "<<endl;
    bfs(root1);
    cout<<"Binary Tree From Preorder and Inorder : "<<endl;
    int in[] = {3,2,8,4,1,6,7,5};
    int pre[] = {1,2,3,4,8,5,6,7};
    BinaryTreeNode *root2 = treeFromPreIn(in,pre,0,7);
    bfs(root2);
    cout<<"Before    Mirroring : "<<endl;
    bfs(root);
    mirror(root);
    cout<<"After Mirroring : "<<endl;
    bfs(root);
    int maxlevel=-1;
    rightView(root,0,maxlevel);
	return 0;
}
