#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    string name;
    vector<Node*> children;

    Node(string n) : name(n) {}
};

void buildBookStructure(Node* parent, const string& level) {
    int numItems;
    cout << "Enter number of " << level << "s in " << parent->name << ": ";
    cin >> numItems;
    cin.ignore(); // Clear input buffer

    for (int i = 1; i <= numItems; ++i) {
        string itemName;
        cout << "Enter " << level << " " << i << " name: ";
        getline(cin, itemName);

        Node* newNode = new Node(itemName);
        parent->children.push_back(newNode);

        if (level == "Chapter") {
            buildBookStructure(newNode, "Section");
        } else if (level == "Section") {
            buildBookStructure(newNode, "Subsection");
        }
    }
}

void printTree(Node* root, int depth = 0) {
    if (!root) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << root->name << endl;
    for (size_t i = 0; i < root->children.size(); ++i) {
        printTree(root->children[i], depth + 1);
    }
}

void deleteTree(Node* root) {
    if (!root) return;
    for (size_t i = 0; i < root->children.size(); ++i) {
        deleteTree(root->children[i]);
    }
    delete root;
}

int main() {
    Node* book = new Node("Book");

    cout << "--- Building Book Structure ---" << endl;
    buildBookStructure(book, "Chapter");

    cout << "\n--- Book Structure ---" << endl;
    printTree(book);

    deleteTree(book);
    return 0;
}



//output:-
//
//
//
//--- Building Book Structure ---
//Enter number of Chapters in Book: 2
//Enter Chapter 1 name: Ad
//Enter number of Sections in Ad: 1
//Enter Section 1 name: Q
//Enter number of Subsections in Q: 1
//Enter Subsection 1 name: q
//Enter Chapter 2 name: Bc
//Enter number of Sections in Bc: 1
//Enter Section 1 name: E
//Enter number of Subsections in E: 1
//Enter Subsection 1 name: G
//
//--- Book Structure ---
//Book
//  Ad
//    Q
//      q
//  Bc
//    E
//      G
//
//--------------------------------
//Process exited after 56.84 seconds with return value 0
//Press any key to continue . . .



//Flowchat:-
//
//
//
//START
//  ¦
//  +- 1. Create "Book" (root node)
//  ¦
//  +- 2. Ask user: "Number of Chapters?"
//  ¦   ¦
//  ¦   +- 3. For each Chapter:
//  ¦   ¦     ¦
//  ¦   ¦     +- 3a. Ask Chapter name
//  ¦   ¦     ¦
//  ¦   ¦     +- 3b. Ask "Number of Sections?"
//  ¦   ¦     ¦   ¦
//  ¦   ¦     ¦   +- 4. For each Section:
//  ¦   ¦     ¦   ¦     ¦
//  ¦   ¦     ¦   ¦     +- 4a. Ask Section name
//  ¦   ¦     ¦   ¦     ¦
//  ¦   ¦     ¦   ¦     +- 4b. Ask "Number of Subsections?"
//  ¦   ¦     ¦   ¦     ¦   ¦
//  ¦   ¦     ¦   ¦     ¦   +- 5. For each Subsection:
//  ¦   ¦     ¦   ¦     ¦         +- 5a. Ask Subsection name
//  ¦   ¦     ¦   ¦     ¦         +- Add to Section
//  ¦   ¦     ¦   ¦     ¦
//  ¦   ¦     ¦   ¦     +- Add to Chapter
//  ¦   ¦     ¦   ¦
//  ¦   ¦     ¦   +- Add to Book
//  ¦   ¦     ¦
//  ¦   ¦     +- Repeat for next Chapter
//  ¦   ¦
//  +- 6. Print Tree (indent based on depth)
//  ¦
//  +- 7. Free Memory (delete all nodes)
//  ¦
//  +- 8. END
