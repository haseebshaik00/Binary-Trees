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

BinaryTreeNode * levelorderBuild(BinaryTreeNode *root,int a[],int i,int n)
{
    if(i>n)
        return NULL;
    root = new BinaryTreeNode(a[i]);
    root->left = levelorderBuild(root->left,a,2*i+1,n);
    root->right = levelorderBuild(root->right,a,2*i+2,n);
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
    if(k==0)
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
    for(int i=0;i<height;i++)
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

BinaryTreeNode * treeFromPostIn(int in[],int post[],int s,int e)
{
    static int f = 7;   // static cz when the recursion comes back the variable will backtrack and we don't want that
    if(s>e)
        return NULL;
    BinaryTreeNode *root  = new BinaryTreeNode(post[f]);
    int index = -1;
    for(int j=s;j<=e;j++)
    {
        if(in[j]==post[f])
        {
            index=j;
            break;
        }
    }
    f--;
    root->right = treeFromPostIn(in,post,index+1,e);
    root->left = treeFromPostIn(in,post,s,index-1);
    return root;
}

int search(int a[], int s, int e, int value)
{
    for (int i = s; i <= e; i++)
        if (a[i] == value)
            return i;
    return -1;
}

int *extrackKeys(int in[], int level[], int m, int n)
{
    int *newlevel = new int[m+5];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (search(in, 0, m-1, level[i]) != -1)
            {
                newlevel[j] = level[i];
                j++;
            }
    return newlevel;
}

BinaryTreeNode *treeFromLevelIn(int in[], int level[], int s, int e,int n)
{
    if(s>e || n<=0)
        return NULL;
    BinaryTreeNode *root = new BinaryTreeNode(level[0]);
    if (s == e)
        return root;
    int i = search(in, s, e, root->data);
    int *llevel  = extrackKeys(in, level, i, n);
    int *rlevel  = extrackKeys(in + i + 1, level, e-i, n);
    root->left = treeFromLevelIn(in, llevel, s, i-1, i-s);
    root->right = treeFromLevelIn(in, rlevel, i+1, e, e-i);
    return root;
}

BinaryTreeNode * treeFromPrePost(int pre[],int post[],int s,int e)
{
    static int i=0;
    if(s>e)
        return NULL;
    BinaryTreeNode *root  = new BinaryTreeNode(pre[i]);
    i++;
    int index = -1;
    for(int j=s;j<=e;j++)
    {
        if(post[j]==pre[i])
        {
            index=j;
            break;
        }
    }
    if(index!=-1)
    {
        root->left = treeFromPrePost(pre,post,s,index);
        root->right = treeFromPrePost(pre,post,index+1,e);
    }
    return root;
}

BinaryTreeNode * treeFromPrePreM(int pre[],int prem[],int s,int e)
{
    static int i=0;
    if(s>e)
        return NULL;
    BinaryTreeNode *root = new BinaryTreeNode(pre[i]);
    i++;
    int index=-1;
    for (int j=s; j<=e;j++)
    {
        if (pre[i] == prem[j])
        {
            index=j;
            break;
        }
    }
    if(index!=-1)
    {
        root->left = treeFromPrePreM(pre,prem,index,e);
        root->right = treeFromPrePreM(pre,prem,s+1,index-1);
    }
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

int printAtDistK(BinaryTreeNode *root, BinaryTreeNode *target, int k)
{
    if(root==NULL)
        return -1;
    if(root==target)
    {
        printKthlevel(target,k);
        return 0;
    }
    int DL = printAtDistK(root->left,target,k);
    if(DL!=-1)
    {
        if(DL+1==k)
            cout<<root->data<<" ";
        else
            printKthlevel(root->right,k-2-DL);
        return 1+DL;
    }
    int DR = printAtDistK(root->right,target,k);
    if(DR!=-1)
    {
        if(DR+1==k)
            cout<<root->data<<" ";
        else
            printKthlevel(root->left,k-2-DR);
        return 1+DR;
    }
    return -1;
}

BinaryTreeNode * lca(BinaryTreeNode *root, int a, int b)
{
    if(root==NULL)
        return NULL;
    if(root->data==a || root->data==b)
        return root;
    BinaryTreeNode *left = lca(root->left,a,b);
    BinaryTreeNode *right = lca(root->right,a,b);
    if(left!=NULL && right!=NULL)
        return root;
    if(left!=NULL)
        return left;
    return right;
}

class PairMaxSum
{
public:
    int branch_sum;
    int max_sum;
    PairMaxSum ()
    {
        branch_sum=0;
        max_sum = 0;
    }
};

PairMaxSum maxSumPath(BinaryTreeNode *root)
{
    PairMaxSum p;
    if(root==NULL)
        return p;
    PairMaxSum left = maxSumPath(root->left);
    PairMaxSum right = maxSumPath(root->right);
    int op1 = root->data;
    int op2 = left.branch_sum + root->data;
    int op3 = right.branch_sum + root->data;
    int op4 = left.branch_sum + right.branch_sum + root->data;

    int current_ans_through_root = max(op1,max(op2,max(op3,op4)));

    p.branch_sum = max(left.branch_sum,max(right.branch_sum,0))+root->data;
    p.max_sum = max(left.max_sum,max(right.max_sum,current_ans_through_root));
    return p;
}

int nodeLength(BinaryTreeNode *root, int key, int level)
{
    if(root==NULL)
        return -1;
    if(root->data==key)
        return level;
    int left = nodeLength(root->left,key,level+1);
    if(left!=-1)
        return left;
    return nodeLength(root->right,key,level+1);
}

int findDistance(BinaryTreeNode *root, int a, int b)
{
    BinaryTreeNode *la = lca(root,a,b);
    int l1 = nodeLength(la,a,0);
    int l2 = nodeLength(la,b,0);
    return l1+l2;
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
	//sumReplacement(root);
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
    cout<<"Before Mirroring : "<<endl;
    bfs(root);
    //mirror(root);
    cout<<"After Mirroring : "<<endl;
    bfs(root);
    cout<<"Right View : ";
    int maxlevel=-1;
    rightView(root,0,maxlevel);
    cout<<endl<<"Kth dist nodes : ";
    BinaryTreeNode * target = root->left;
    printAtDistK(root,target,1);
    cout<<endl;
    cout<<"LCA : "<<lca(root,6,1)->data<<endl;
    cout<<"Max Sum Path : "<<maxSumPath(root).max_sum<<endl;
    cout<<"Shortest Distance : "<<findDistance(root,6,1)<<endl;
    int a1[] = {10,20,30,40,50,60,70,80,90};
    BinaryTreeNode *root6;
    BinaryTreeNode *root7 = levelorderBuild(root,a1,0,8);
    bfs(root6);
    int in1[]   = {4, 8, 2, 5, 1, 6, 3, 7};
    int post[] = {8, 4, 5, 2, 6, 7, 3, 1};
    //BinaryTreeNode *root9 = treeFromPostIn(in1,post,0,7);
    //bfs(root9);
    //int in2[]    = {4, 8, 10, 12, 14, 20, 22};
    //int level[] = {20, 8, 22, 4, 12, 10, 14};
    //BinaryTreeNode *root10 = treeFromLevelIn(in2,level,0,6,7);
    //bfs(root10);
    //int pre[] = {1, 2, 4, 8, 9, 5, 3, 6, 7};
    //int post[] = {8, 9, 4, 5, 2, 6, 7, 3, 1};
    //BinaryTreeNode *root11 = treeFromPrePost(pre,post,0,8);
    //bfs(root11);
    //int pre[] = {1, 2, 4, 5, 3, 6, 7};
    //int prem[] =  {1 ,3 ,7 ,6 ,2 ,5 ,4};
    //BinaryTreeNode *root12 = treeFromPrePreM(pre,prem,0,6);
    //bfs(root12);
    cout<<endl<<"Binary Search Tress"<<endl;
	return 0;
}
