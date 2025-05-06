#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    return root;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findLongestPath(Node* root) {
    if (root == NULL) return 0;
    return 1 + max(findLongestPath(root->left), findLongestPath(root->right));
}

int findMinValue(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return -1;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

Node* mirrorTree(Node* root) {
    if (root == NULL) return NULL;
    Node* temp = root->left;
    root->left = mirrorTree(root->right);
    root->right = mirrorTree(temp);
    return root;
}

bool searchValue(Node* root, int value) {
    if (root == NULL) return false;
    if (root->data == value) return true;
    if (value < root->data) return searchValue(root->left, value);
    return searchValue(root->right, value);
}

void inorderTraversal(Node* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

int main() {
    Node* root = NULL;
    int choice, value, n;

    cout << "Enter number of initial nodes: ";
    cin >> n;
    cout << "Enter values to insert:\n";
    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insertNode(root, value);
    }

    do {
        cout << "\nBST Operations:\n";
        cout << "1. Insert node\n";
        cout << "2. Longest path from root\n";
        cout << "3. Find minimum value\n";
        cout << "4. Mirror tree\n";
        cout << "5. Search value\n";
        cout << "6. Display tree (inorder)\n";
        cout << "7. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                root = insertNode(root, value);
                cout << value << " inserted!\n";
                break;
            case 2:
                cout << "Longest path: " << findLongestPath(root) << endl;
                break;
            case 3:
                cout << "Minimum value: " << findMinValue(root) << endl;
                break;
            case 4:
                root = mirrorTree(root);
                cout << "Tree mirrored! Inorder: ";
                inorderTraversal(root);
                cout << endl;
                break;
            case 5:
                cout << "Enter value to search: ";
                cin >> value;
                if (searchValue(root, value))
                    cout << value << " found!\n";
                else
                    cout << value << " not found!\n";
                break;
            case 6:
                cout << "Inorder traversal: ";
                inorderTraversal(root);
                cout << endl;
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
            case 8:
                cout << "Exiting...\n";
                break;
          
        }
    } while(choice != 7);

    return 0;
}  



//output:-
//
//
//Enter number of initial nodes: 6
//Enter values to insert:
//5
//8
//0
//6
//8
//9
//
//BST Operations:
//1. Insert node
//2. Longest path from root
//3. Find minimum value
//4. Mirror tree
//5. Search value
//6. Display tree (inorder)
//7. Exit
//Choice: 3
//Minimum value: 0
//
//BST Operations:
//1. Insert node
//2. Longest path from root
//3. Find minimum value
//4. Mirror tree
//5. Search value
//6. Display tree (inorder)
//7. Exit
//Choice: 4
//Tree mirrored! Inorder: 9 8 6 5 0
//
//BST Operations:
//1. Insert node
//2. Longest path from root
//3. Find minimum value
//4. Mirror tree
//5. Search value
//6. Display tree (inorder)
//7. Exit
//Choice: 6
//Inorder traversal: 9 8 6 5 0
//
//BST Operations:
//1. Insert node
//2. Longest path from root
//3. Find minimum value
//4. Mirror tree
//5. Search value
//6. Display tree (inorder)
//7. Exit
//Choice:
	
	
	
