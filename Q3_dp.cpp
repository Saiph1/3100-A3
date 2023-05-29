#include <iostream>
#include <vector> 
using namespace std; 

// Return the max sum of the route.
int Q3(vector<vector<int>> tree, int levels){
    for (int i = levels-2; i >= 0; --i){ 
        for (unsigned int j = 0; j<tree[i].size(); j++){ 
            if (tree[i+1][j]>=tree[i+1][j+1]) tree[i][j]+=tree[i+1][j];
            else tree[i][j]+=tree[i+1][j+1];
            
        }
    }
    return tree[0][0]; 
}

int main(){

    // User must input the number of levels of the triangle.
    int levels;
    vector<vector<int>> triangle; 
    cout << "Input the number of the levels of the tree: "; cin >> levels; 
    // Input the whole tree from the top to the bottom manually. 
    for(int i = 0; i < levels; i++){
        vector<int> tmp;
        for (int j = 0; j< i+1; j++){
            cout << "Input the "<< j+1 << "th node data of the " << i+1 << "th row (From left to right): " << endl;  
            int element;   
            cin >> element; 
            tmp.push_back(element);
        }
        triangle.push_back(tmp);
    }
    cout << "Your input tree is: " << endl; 
    // Printing trees from the stored tree in the 2D vector. 
    for (int i= 0; i <levels; i++){ 
        for(int j = 0; j<levels-i; j++) 
            cout <<" "; 
        for(unsigned int k = 0; k<triangle[i].size(); k++)
            cout << triangle[i][k] << " "; 
        cout << endl; 
    }   
    cout << "Maximum route sum = " << Q3(triangle, levels);  

    return 0; 
}