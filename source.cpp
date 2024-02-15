#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct tree
{
    int val;
    struct tree* left;
    struct tree* right;
    tree(int x): val(x), left(nullptr), right(nullptr) {}
};

tree* rLCA(tree* root, int p, int q)
{
    if(root == NULL) return NULL;
    if((p <= root->val && root->val <= q) || (p >= root->val && root->val >= q)) return root;
    if(p < root->val && q < root->val) return rLCA(root->left, p, q);
    if(p > root->val && q > root->val) return rLCA(root->right, p, q);
    return NULL;
}

tree* iLCA(tree* root, int p, int q)
{
    tree* node = root;
    while(node != NULL)
    {
        if(node->val > p && node->val > q)
            node = node->left;
        else if(node->val < p && node->val < q)
            node = node->right;
        else
            return node;
    }
    return NULL;
}

struct tree* createTree(vector<int> &arr, int start, int end)
{
    if (start > end) {
        return NULL;
    }
    struct tree* node = new tree(arr[start]);
    int i;
    for (i = start; i <= end; i++)
    {
        if (arr[i] > node->val) {
            break;
        }
    }
    node->left = createTree(arr, start + 1, i - 1);
    node->right = createTree(arr, i, end);
    return node;
}

void prnt (tree* node)
{
    if (node == NULL)  
    {
       return;
    }
    prnt(node->left);  
    cout << node->val << " ";
    prnt(node->right);
}
 
vector<int> convertStoI(string str)
{
    int str_length = str.length();
    int arr[str_length];
    int j = 0, i, sum = 0;
    for (i = 0; i<str.length(); i++) {
        if (str[i] == ' ' || str[i]=='[' || str[i]==']')
            continue;
         if (str[i] == ','){
            j++;
        }
        else {
            arr[j] = arr[j] * 10 + (str[i] - 48);
        }
    }
    vector <int>res;
    for (i = 0; i <= j; i++) {
        res.push_back(arr[i]);
    }
    return res;
}

int convertCtoI(string str)
{
    int str_length = str.length();
    int arr =  0 ;
    int j = 0, i, sum = 0;
    for (i = 0; i<str.length(); i++) {
            arr = arr * 10 + (str[i] - 48);
    }
    return arr;
}

string converItoC(int s)
{
    return std::to_string(s);
}

string BinarySearchTreeLCA(string strArr[], int arrLength) {

  // code goes here  
    string arr = strArr[0];
    vector<int> a = convertStoI(arr);
    struct tree* root = nullptr;
    root = createTree(a, 0, arrLength+3);
    tree* res = iLCA(root, convertCtoI(strArr[1]), convertCtoI(strArr[2]));
    strArr[0].clear();
    strArr[0]=converItoC(res->val);
    return strArr[0];
}

int main(void) {
  // keep this function call here
  string A[] =  {"[10, 5, 1, 7, 40, 50]", "1", "7"}; // coderbyteInternalStdinFunction(stdin);
  int arrLength = A[0].size();
  cout << BinarySearchTreeLCA(A, arrLength)<<"\n";
  return 0;
}
