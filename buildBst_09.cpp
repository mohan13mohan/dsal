#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Node {
    string key;
    Node* left;
    Node* right;
    Node(string k) : key(k), left(nullptr), right(nullptr) {}
};

// Utility function to print BST in-order
void printBST(Node* root, int level = 0) {
    if (!root) return;
    printBST(root->right, level + 1);
    for (int i = 0; i < level; ++i) cout << "   ";
    cout << root->key << endl;
    printBST(root->left, level + 1);
}

// Build BST from root table
Node* buildOptimalBST(vector<string>& keys, vector<vector<int>>& root, int i, int j) {
    if (i > j) return nullptr;
    int r = root[i][j];
    Node* node = new Node(keys[r]);
    node->left = buildOptimalBST(keys, root, i, r - 1);
    node->right = buildOptimalBST(keys, root, r + 1, j);
    return node;
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    vector<string> keys(n);
    vector<double> p(n);

    cout << "Enter the keys (in sorted order):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Key " << i + 1 << ": ";
        cin >> keys[i];
    }

    cout << "Enter the search probabilities for each key:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Probability for " << keys[i] << ": ";
        cin >> p[i];
    }

    // DP tables
    vector<vector<double>> cost(n, vector<double>(n, 0));
    vector<vector<double>> sum(n, vector<double>(n, 0));
    vector<vector<int>> root(n, vector<int>(n, 0));

    // Initialization
    for (int i = 0; i < n; ++i) {
        cost[i][i] = p[i];
        sum[i][i] = p[i];
        root[i][i] = i;
    }

    // DP filling
    for (int L = 2; L <= n; ++L) { // L = subtree length
        for (int i = 0; i <= n - L; ++i) {
            int j = i + L - 1;
            cost[i][j] = numeric_limits<double>::infinity();
            sum[i][j] = sum[i][j - 1] + p[j];

            for (int r = i; r <= j; ++r) {
                double c = 0;
                if (r > i) c += cost[i][r - 1];
                if (r < j) c += cost[r + 1][j];
                c += sum[i][j];

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "\nMinimum expected search cost: " << cost[0][n - 1] << endl;

    // Build and print tree
    Node* bst = buildOptimalBST(keys, root, 0, n - 1);
    cout << "\nOptimal Binary Search Tree (in visual rotated form):\n";
    printBST(bst);

    return 0;
}


// output:-


// Enter number of keys: 5
// Enter the keys (in sorted order):
// Key 1: 2
// Key 2: 4
// Key 3: 6
// Key 4: 7
// Key 5: 8
// Enter the search probabilities for each key:
// Probability for 2: 1
// Probability for 4: 0.3
// Probability for 6: 0.4
// Probability for 7: 0.5
// Probability for 8: 0.3

// Minimum expected search cost: 5.2

// Optimal Binary Search Tree (in visual rotated form):
//       8
//    7
// 6
//       4
//    2