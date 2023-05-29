#include <iostream>
#include <math.h>
#include <vector> 
using namespace std; 

/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct Node {
    int data;
    struct Node *left, *right;
};
 
// Utility function to create a new tree node
Node* newNode(int data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

//This is necessary as it is used for the recursion for building a tree. This constructed a 2 level depths tree with known children. 
Node* newNode_knownChild(int data, Node* node1, Node* node2)
{
    Node* temp = new Node;
    temp->data = data;
    temp->left = node1; 
    temp->right = node2 ;
    return temp;
}

// This returns the maximum depths of the tree. 
// Taken online. 
int maxDepth(Node* node)
{
    if (node == NULL)
        return 0;
    else {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
 
        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

// Copied online.
// Print the tree in pre-order sequence. 
void printPreorder(struct Node* node)
{
    if (node == NULL)
        return;

    /* first print data of node */
    cout << node->data << "(" << maxDepth(node) <<")"<< " " ;
    // The numbers in the bracket stands for the level of the node in which it belongs to. 

    /* then recur on left subtree */
    printPreorder(node->left);
 
    /* now recur on right subtree */
    printPreorder(node->right);
}
 

Node* reduce_node(Node* node){
    if (maxDepth(node)==2){
        Node* temp = new Node;
        // E.g. A two level tree is a tree with depth = 2, like  7
        //                                                      3 8
        // If the left child is NULL, the 2 level tree reduced to a node summing its data and the right child data. 
        if (!node->left) temp->data = node->right->data; 
        // If the right child is NULL, the 2 level tree reduced to a node summing its data and the left child data. 
        else if (!node->right) temp->data = node->left->data; 
        // If two child is not NULL, the 2 level tree reduced to a node summing its data and the child with largest number (data). 
        else temp->data = (node->left->data >= node->right->data ? node->data + node->left->data: node->data+ node->right->data);
        temp->left = temp->right = NULL;
        return temp;
    }
    return newNode_knownChild(node->data, node->left?reduce_node(node->left):NULL, node->right?reduce_node(node->right):NULL);

}

// The actual implementation of the question 2 algorithm in recursive manner. 
Node* Q3(Node* node){
    // printPreorder(node);
    // cout << endl; 
    if (maxDepth(node) ==1)
        return node; 
    // Recursion until the tree has only depth = 1, theoretically, the node data is the largest sum of the data route. 
    else return Q3(reduce_node(node));
}

// This is used to convert a flattened tree stored in the vector v1 to the actual tree in node data structure.
Node* convert_tree(vector<int> v1, int total_level, int ind, int level=1){
    // If it reaches the last level of the tree. 
    if (level == total_level){
        return newNode(v1[ind]);
    } 
    else{ 
        return newNode_knownChild(v1[ind], convert_tree(v1, total_level, ind+level, level+1), convert_tree(v1, total_level, ind+level+1, level+1));
    }
}
 
int main(){

    int levels;
    cout << "Input the numbers of the levels: "; cin >> levels; 
    vector<int> tree;
    // Storing the tree in a vector (flattened 1D). 
    for(int i = 0; i < levels; i++){
        for (int j = 0; j< i+1; j++){
            cout << "Input the "<< j+1 << "th node data of the " << i+1 << "th row (From left to right): " << endl;  
            int tmp; 
            cin >> tmp;
            tree.push_back(tmp); 
        }
    }
    cout << "Your input tree is : " << endl; 
    // Printing trees from the stored tree in the vector. 
    for (int i= 0; i <levels; i++){ 
        for(int j = 0; j<levels-i; j++) 
            cout <<"  "; 
        for(int k = 0; k<i+1; k++)
            // Quadratic sequence (first row start from index 0, second 1, third 3, forth, 6 and so on...)
            cout << tree[0.5*pow(i+1, 2)-0.5*(i+1)+k] <<"  "; 
        cout << endl; 
    }   
    // Example1 : 
    //    7
    //   3 8
    //  8 1 0
    // 2 7 4 4
    // struct Node* root = newNode(7);
    // root->left = newNode(3);
    // root->right = newNode(8);
    // root->left->left = newNode(8);
    // root->left->right = newNode(1);
    // root->right->left = newNode(1);
    // root->right->right = newNode(0);
    // root->left->left->left = newNode(2);
    // root->left->left->right = newNode(7);
    // root->left->right->left = newNode(7);
    // root->left->right->right = newNode(4);
    // root->right->left->left = newNode(7);
    // root->right->left->right = newNode(4);
    // root->right->right->left = newNode(4);
    // root->right->right->right = newNode(4);
    // Quesation 1): 
    //       1
    //      5 3
    //    11 9 10
    //   8 15 17 1
    // 11 32 25 27 9
    // struct Node* root = newNode(1);
    // root->left = newNode(5);
    // root->right = newNode(3);
    // root->left->left = newNode(11);
    // root->left->right = newNode(9);
    // root->right->left = newNode(9);
    // root->right->right = newNode(10);
    // root->left->left->left = newNode(8);
    // root->left->left->right = newNode(15);
    // root->left->right->left = newNode(15);
    // root->left->right->right = newNode(17);
    // root->right->left->left = newNode(15);
    // root->right->left->right = newNode(17);
    // root->right->right->left = newNode(17);
    // root->right->right->right = newNode(1);
    // root->left->left->left->left = newNode(11);
    // root->left->left->left->right = newNode(32);
    // root->left->left->right->left = newNode(32);
    // root->left->left->right->right = newNode(25);
    // root->left->right->left->left = newNode(32);
    // root->left->right->left->right = newNode(25);
    // root->left->right->right->left = newNode(25);
    // root->left->right->right->right = newNode(27);
    // root->right->left->left->left = newNode(32);
    // root->right->left->left->right = newNode(25);
    // root->right->left->right->left = newNode(25);
    // root->right->left->right->right = newNode(27);
    // root->right->right->left->left = newNode(25);
    // root->right->right->left->right = newNode(27);
    // root->right->right->right->left = newNode(27);
    // root->right->right->right->right = newNode(9);

    // Function call
    // cout << Q3(root)->data;
    // int sum1 = Q3(root)->data; 
    // cout << "Converted tree printed in pre-order = " << endl; 
    int sum2 = Q3(convert_tree(tree, levels, 0))->data;
    // cout << "The largest sum of the route for Sum1 = " << sum1 << endl ;
    cout << "The largest sum of the route = " << sum2 ;
    // cout << reduce_node(root)->data; 
    // cout << (1<NULL);
    return 0;
}