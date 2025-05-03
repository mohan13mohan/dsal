#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Tree node definition
class TreeNode {
public:
    string name;
    vector<TreeNode*> children;

    TreeNode(string name) {
        this->name = name;
    }

    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    void printTree(int level = 0) {
        for (int i = 0; i < level; ++i)
            cout << "  ";
        cout << name << endl;
        for (TreeNode* child : children)
            child->printTree(level + 1);
    }

    ~TreeNode() {
        for (TreeNode* child : children)
            delete child;
    }
};

int main() {
    // Constructing the book tree
    TreeNode* book = new TreeNode("Book Title");

    // Adding chapters
    TreeNode* chapter1 = new TreeNode("Chapter 1");
    TreeNode* chapter2 = new TreeNode("Chapter 2");
    book->addChild(chapter1);
    book->addChild(chapter2);

    // Adding sections to Chapter 1
    TreeNode* section1_1 = new TreeNode("Section 1.1");
    TreeNode* section1_2 = new TreeNode("Section 1.2");
    chapter1->addChild(section1_1);
    chapter1->addChild(section1_2);

    // Adding subsections to Section 1.1
    TreeNode* subsection1_1_1 = new TreeNode("Subsection 1.1.1");
    TreeNode* subsection1_1_2 = new TreeNode("Subsection 1.1.2");
    section1_1->addChild(subsection1_1_1);
    section1_1->addChild(subsection1_1_2);

    // Adding section to Chapter 2
    TreeNode* section2_1 = new TreeNode("Section 2.1");
    chapter2->addChild(section2_1);

    // Print the entire tree
    book->printTree();

    // Free memory
    delete book;

    return 0;
}



// Output:-

// Book Title
//   Chapter 1
//     Section 1.1
//       Subsection 1.1.1
//       Subsection 1.1.2
//     Section 1.2
//   Chapter 2
//     Section 2.1
