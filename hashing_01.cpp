#include <iostream>
#include <list>
#include <string>
using namespace std;

const int TABLE_SIZE = 10; // Choose a small size for demo

// Structure for storing client data
struct Client {
    string name;        // Key
    string phoneNumber; // Value
};

// Hash function
int hashFunction(string key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % TABLE_SIZE;
}

// ----------- Chaining -------------
class HashTableChaining {
    list<Client> table[TABLE_SIZE];

public:
    void insert(string name, string phoneNumber) {
        int index = hashFunction(name);
        for (auto &client : table[index]) {
            if (client.name == name) {
                client.phoneNumber = phoneNumber; // Update
                return;
            }
        }
        table[index].push_back({name, phoneNumber});
    }

    bool search(string name, string &phone, int &comparisons) {
        int index = hashFunction(name);
        comparisons = 0;
        for (auto &client : table[index]) {
            comparisons++;
            if (client.name == name) {
                phone = client.phoneNumber;
                return true;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            for (auto &client : table[i]) {
                cout << "[" << client.name << ": " << client.phoneNumber << "] -> ";
            }
            cout << "NULL\n";
        }
    }
};

// ----------- Linear Probing -------------
class HashTableLinearProbing {
    Client* table[TABLE_SIZE];
    bool occupied[TABLE_SIZE];

public:
    HashTableLinearProbing() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
            occupied[i] = false;
        }
    }

    void insert(string name, string phoneNumber) {
        int index = hashFunction(name);
        int startIndex = index;
        while (occupied[index]) {
            if (table[index]->name == name) {
                table[index]->phoneNumber = phoneNumber;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                cout << "Hash table is full\n";
                return;
            }
        }
        table[index] = new Client{name, phoneNumber};
        occupied[index] = true;
    }

    bool search(string name, string &phone, int &comparisons) {
        int index = hashFunction(name);
        int startIndex = index;
        comparisons = 0;
        while (occupied[index]) {
            comparisons++;
            if (table[index]->name == name) {
                phone = table[index]->phoneNumber;
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) break;
        }
        return false;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i]) {
                cout << i << ": [" << table[i]->name << ": " << table[i]->phoneNumber << "]\n";
            } else {
                cout << i << ": NULL\n";
            }
        }
    }
};

// ----------- Main -------------
int main() {
    HashTableChaining chaining;
    HashTableLinearProbing linear;

    // Sample data
    chaining.insert("Jay", "111-1111");
    chaining.insert("Bagul B.", "222-2222");
    chaining.insert("Anup C.", "333-3333");
    chaining.insert("Raja Harsh", "444-4444");

    linear.insert("Jay", "111-1111");
    linear.insert("Bagul B.", "222-2222");
    linear.insert("Anup C.", "333-3333");
    linear.insert("Raja Harsh", "444-4444");

    cout << "Hash Table (Chaining):\n";
    chaining.display();
    cout << "\nHash Table (Linear Probing):\n";
    linear.display();

    // Test searching
    string phone;
    int comparisons;

    string searchName = "Anup C.";
    if (chaining.search(searchName, phone, comparisons))
        cout << "\n[Chaining] Found " << searchName << " in " << comparisons << " comparisons: " << phone << "\n";
    else
        cout << "\n[Chaining] " << searchName << " not found.\n";

    if (linear.search(searchName, phone, comparisons))
        cout << "[Linear Probing] Found " << searchName << " in " << comparisons << " comparisons: " << phone << "\n";
    else
        cout << "[Linear Probing] " << searchName << " not found.\n";

    return 0;
}





// Output:-

// Hash Table (Chaining):
// 0: NULL
// 1: NULL
// 2: [Jay: 111-1111] -> NULL
// 3: NULL
// 4: NULL
// 5: [Bagul B.: 222-2222] -> NULL
// 6: [Raja Harsh: 444-4444] -> NULL
// 7: NULL
// 8: NULL
// 9: [Anup C.: 333-3333] -> NULL

// Hash Table (Linear Probing):
// 0: NULL
// 1: NULL
// 2: [Jay: 111-1111]
// 3: NULL
// 4: NULL
// 5: [Bagul B.: 222-2222]
// 6: [Raja Harsh: 444-4444]
// 7: NULL
// 8: NULL
// 9: [Anup C.: 333-3333]

// [Chaining] Found Anup C. in 1 comparisons: 333-3333
// [Linear Probing] Found Anup C. in 1 comparisons: 333-3333
