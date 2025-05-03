#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

// Tree node
struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

// Helper function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Construct expression tree from prefix expression
TreeNode* constructTree(const string& prefix) {
    stack<TreeNode*> stk;

    // Traverse from right to left
    for (int i = prefix.length() - 1; i >= 0; --i) {
        char ch = prefix[i];
        TreeNode* node = new TreeNode(ch);

        if (isOperator(ch)) {
            // Pop two operands for the operator
            if (!stk.empty()) node->left = stk.top(), stk.pop();
            if (!stk.empty()) node->right = stk.top(), stk.pop();
        }

        stk.push(node);
    }

    return stk.top();
}

// Post-order traversal (non-recursive)
void postOrderTraversal(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        TreeNode* node = s1.top(); s1.pop();
        s2.push(node);

        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->val << " ";
        s2.pop();
    }
    cout << endl;
}

// Delete the tree (post-order recursive)
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Main
int main() {
    string prefix = "+--a*bc/def";

    // Step 1: Construct expression tree
    TreeNode* root = constructTree(prefix);

    // Step 2: Non-recursive post-order traversal
    cout << "Post-order traversal: ";
    postOrderTraversal(root);

    // Step 3: Delete the tree
    deleteTree(root);

    return 0;
}



// output:-

// Post-order traversal: a b c * - d e / - f + 