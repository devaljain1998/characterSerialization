#include <bits/stdc++.h>
#define MARKER -1 
using namespace std;

struct Node 
{ 
    char key; 
    struct Node* left, *right; 
}; 
  
Node* newNode(char key) 
{ 
    Node* temp = new Node; 
    temp->key = key; 
    temp->left = temp->right = NULL; 
    return (temp); 
} 
  
// This function stores a tree in a file pointed by fp 
void serialize(Node *root, FILE *fp) 
{ 
    // If current node is NULL, store marker 
    if (root == NULL) 
    { 
        fprintf(fp, "%c ", '#'); 
        return; 
    } 
  
    // Else, store current node and recur for its children 
    fprintf(fp, "%c ", root->key); 
    serialize(root->left, fp); 
    serialize(root->right, fp); 
} 
  
// This function constructs a tree from a file pointed by 'fp' 
void deSerialize(Node *&root, FILE *fp) 
{ 
    // Read next item from file. If theere are no more items or next 
    // item is marker, then return 
    char val; 
    if ( !fscanf(fp, "%c ", &val) || val == '#') 
       return; 
  
    // Else create node with this item and recur for children 
    root = newNode(val); 
    deSerialize(root->left, fp); 
    deSerialize(root->right, fp); 
} 

Node* insert(Node* node, char key) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key <= node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key);    
  
    /* return the (unchanged) node pointer */
    return node; 
}
  
// A simple inorder traversal used for testing the constructed tree 
void inorder(Node *root) 
{ 
    if (root) 
    { 
        inorder(root->left); 
        printf("%c ", root->key); 
        inorder(root->right); 
    } 
} 

void printPostorder(struct Node* node) 
{ 
    if (node == NULL) 
        return; 
  
    // first recur on left subtree 
    printPostorder(node->left); 
  
    // then recur on right subtree 
    printPostorder(node->right); 
  
    // now deal with the node 
    cout << node->key << " "; 
} 

void printPreorder(struct Node* node) 
{ 
    if (node == NULL) 
        return; 
  
    /* first print data of node */
    cout << node->key << " "; 
  
    /* then recur on left sutree */
    printPreorder(node->left);  
  
    /* now recur on right subtree */
    printPreorder(node->right); 
}


int main(int argc, char** argv) {

    FILE *fp = fopen("csv-file.csv", "r"); 
    FILE *wp = fopen("serialized-output.bin", "w+"); 

    if (fp == NULL) { 
        puts("Could not open file"); 
        return 0; 
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        //cout << "Value of Read is: " << read << " and line is " << line << endl;
        Node* newRoot = NULL;
        newRoot = insert(newRoot, line[0]);
        for (int i=1; i<len; i++) {
            //cout << line[i];
            insert(newRoot, line[i]);
        }
        //cout << "Inorder: "; inorder(newRoot);cout << endl;
        serialize(newRoot, wp); 
        //fprintf(wp, "\n");
    }
    fclose(fp); 
    fclose(wp);

    
    // Let us deserialize the stored tree into root1 
    Node *root1 = NULL; 

    fp = fopen("serialized-output.bin", "r"); 
    try
    {
        while ((read = getline(&line, &len, fp)) != -1) {
            Node* newRoot = NULL;
            for (int i=0; i<len; i++) {
                deSerialize(newRoot, fp);
            }
            cout << "Successfully deserialized\n" ;
        }
    }
    catch(const std::exception& e) {
        cout << e.what() << '\n';
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}