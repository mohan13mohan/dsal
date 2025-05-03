#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;
    int height;

    Node(string k, string m) : keyword(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

// Utility to get height
int height(Node* node) {
    return node ? node->height : 0;
}

// Utility to get balance factor
int getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Update height
void updateHeight(Node* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

// Right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Insert a keyword
Node* insert(Node* root, string keyword, string meaning) {
    if (!root)
        return new Node(keyword, meaning);

    if (keyword < root->keyword)
        root->left = insert(root->left, keyword, meaning);
    else if (keyword > root->keyword)
        root->right = insert(root->right, keyword, meaning);
    else {
        cout << "Keyword already exists. Use update option.\n";
        return root;
    }

    updateHeight(root);
    int balance = getBalance(root);

    // Left Left
    if (balance > 1 && keyword < root->left->keyword)
        return rotateRight(root);
    // Right Right
    if (balance < -1 && keyword > root->right->keyword)
        return rotateLeft(root);
    // Left Right
    if (balance > 1 && keyword > root->left->keyword) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Right Left
    if (balance < -1 && keyword < root->right->keyword) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Minimum value node
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

// Delete a keyword
Node* deleteNode(Node* root, string keyword) {
    if (!root) return nullptr;

    if (keyword < root->keyword)
        root->left = deleteNode(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteNode(root->right, keyword);
    else {
        // Node with one or no child
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }

        // Node with two children
        Node* temp = minValueNode(root->right);
        root->keyword = temp->keyword;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->keyword);
    }

    updateHeight(root);
    int balance = getBalance(root);

    // Balancing
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Update a meaning
bool updateMeaning(Node* root, string keyword, string newMeaning) {
    if (!root) return false;

    if (keyword < root->keyword)
        return updateMeaning(root->left, keyword, newMeaning);
    else if (keyword > root->keyword)
        return updateMeaning(root->right, keyword, newMeaning);
    else {
        root->meaning = newMeaning;
        return true;
    }
}

// Search a keyword and return comparisons
int search(Node* root, string keyword) {
    int comparisons = 0;
    while (root) {
        comparisons++;
        if (keyword == root->keyword) {
            cout << "Meaning: " << root->meaning << endl;
            return comparisons;
        } else if (keyword < root->keyword) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    cout << "Keyword not found.\n";
    return comparisons;
}

// Display in ascending or descending order
void display(Node* root, bool ascending = true) {
    if (!root) return;
    if (ascending) {
        display(root->left, ascending);
        cout << root->keyword << ": " << root->meaning << endl;
        display(root->right, ascending);
    } else {
        display(root->right, ascending);
        cout << root->keyword << ": " << root->meaning << endl;
        display(root->left, ascending);
    }
}

// Driver
int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;
    bool asc;

    while (true) {
        cout << "\n1. Add keyword\n2. Delete keyword\n3. Update meaning\n4. Search keyword"
             << "\n5. Display ascending\n6. Display descending\n7. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter keyword: "; cin >> key;
                cout << "Enter meaning: "; cin.ignore(); getline(cin, meaning);
                root = insert(root, key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: "; cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter keyword to update: "; cin >> key;
                cout << "Enter new meaning: "; cin.ignore(); getline(cin, meaning);
                if (!updateMeaning(root, key, meaning))
                    cout << "Keyword not found.\n";
                break;
            case 4:
                cout << "Enter keyword to search: "; cin >> key;
                cout << "Comparisons made: " << search(root, key) << endl;
                break;
            case 5:
                cout << "\nDictionary in Ascending Order:\n";
                display(root, true);
                break;
            case 6:
                cout << "\nDictionary in Descending Order:\n";
                display(root, false);
                break;
            case 7:
                exit(0);
        }
    }
}



// Output:-


// 1. Add keyword
// 2. Delete keyword
// 3. Update meaning
// 4. Search keyword
// 5. Display ascending
// 6. Display descending
// 7. Exit
// Choice: 1
// Enter keyword: tyr
// Enter meaning: hii

// 1. Add keyword
// 2. Delete keyword
// 3. Update meaning
// 4. Search keyword
// 5. Display ascending
// 6. Display descending
// 7. Exit
// Choice: 3
// Enter keyword to update: tyr
// Enter new meaning: ij

// 1. Add keyword
// 2. Delete keyword
// 3. Update meaning
// 4. Search keyword
// 5. Display ascending
// 6. Display descending
// 7. Exit
// Choice: 5

// Dictionary in Ascending Order:
// tyr: ij

// 1. Add keyword
// 2. Delete keyword
// 3. Update meaning
// 4. Search keyword
// 5. Display ascending
// 6. Display descending
// 7. Exit
// Choice: 4
// Enter keyword to search: tyr
// Comparisons made: Meaning: ij
// 1

// 1. Add keyword
// 2. Delete keyword
// 3. Update meaning
// 4. Search keyword
// 5. Display ascending
// 6. Display descending
// 7. Exit
// Choice: 7