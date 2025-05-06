#include <iostream>
using namespace std;

struct node {
    int value;
    node* next;
} *HashTable[10];

class hashing {
public:
    hashing() {
        for (int i = 0; i < 10; i++) {
            HashTable[i] = NULL;
        }
    }

    int HashFunction(int value) {
        return (value % 10);
    }

    node* create_node(int x) {
        node* temp = new node;
        temp->next = NULL;
        temp->value = x;
        return temp;
    }

    void display() {
        for (int i = 0; i < 10; i++) {
            node* temp = HashTable[i];
            cout << "a[" << i << "] ";
            while (temp != NULL) {
                cout << "-> " << temp->value;
                temp = temp->next;
            }
            cout << endl;
        }
    }

    int searchElement(int value) {
        bool flag = false;
        int hash_val = HashFunction(value);
        node* entry = HashTable[hash_val];
        cout << "Element found at: ";
        while (entry != NULL) {
            if (entry->value == value) {
                cout << hash_val << " : " << entry->value << endl;
                flag = true;
            }
            entry = entry->next;
        }
        if (!flag) {
            return -1;
        }
        return 1;
    }

    void deleteElement(int value) {
        int hash_val = HashFunction(value);
        node* entry = HashTable[hash_val];
        node* prev = NULL;

        if (entry == NULL) {
            cout << "No Element found" << endl;
            return;
        }

        if (entry->value == value) {
            HashTable[hash_val] = entry->next;
            delete entry;
            return;
        }

        while (entry != NULL && entry->value != value) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == NULL) {
            cout << "Element not found" << endl;
            return;
        }

        prev->next = entry->next;
        delete entry;
    }

    void insertElement(int value) {
        int hash_val = HashFunction(value);
        node* head = create_node(value);
        node* temp = HashTable[hash_val];

        if (temp == NULL) {
            HashTable[hash_val] = head;
        } else {
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = head;
        }
    }
};

int main() {
    int ch;
    int data, search, del;
    hashing h;

    do {
        cout << "Telephone Directory Menu:" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Display" << endl;
        cout << "3. Search" << endl;
        cout << "4. Delete" << endl;
        cout << "5. Exit" << endl;

        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Enter phone number to insert: ";
                cin >> data;
                h.insertElement(data);
                break;
            case 2:
                h.display();
                break;
            case 3:
                cout << "Enter the number to be searched: ";
                cin >> search;
                if (h.searchElement(search) == -1) {
                    cout << "No element found at key." << endl;
                }
                break;
            case 4:
                cout << "Enter the phone number to delete: ";
                cin >> del;
                h.deleteElement(del);
                cout << "Phone number deleted." << endl;
                break;
        }
        cout << endl;
    } while (ch != 5);

    return 0;
}





//output:-
//
//
//Telephone Directory Menu:
//1. Insert
//2. Display
//3. Search
//4. Delete
//5. Exit
//1
//Enter phone number to insert: 5955465
//
//Telephone Directory Menu:
//1. Insert
//2. Display
//3. Search
//4. Delete
//5. Exit
//1
//Enter phone number to insert: 84656526
//
//Telephone Directory Menu:
//1. Insert
//2. Display
//3. Search
//4. Delete
//5. Exit
//2
//a[0]
//a[1]
//a[2]
//a[3]
//a[4]
//a[5] -> 5955465
//a[6] -> 84656526
//a[7]
//a[8]
//a[9]
//
//Telephone Directory Menu:
//1. Insert
//2. Display
//3. Search
//4. Delete
//5. Exit
//3
//Enter the number to be searched: 84656526
//Element found at: 6 : 84656526
//
//Telephone Directory Menu:
//1. Insert
//2. Display
//3. Search
//4. Delete
//5. Exit
//4
//Enter the phone number to delete: 84656526
//Phone number deleted.
//
//Telephone Directory Menu:
//1. Insert
//2. Display
//3. Search
//4. Delete
//5. Exit
//2
//a[0]
//a[1]
//a[2]
//a[3]
//a[4]
//a[5] -> 5955465
//a[6]
//a[7]
//a[8]
//a[9]
//
//Telephone Directory Menu:
//1. Insert
//2. Display
//3. Search
//4. Delete
//5. Exit




//flow chart:-
//
//
//Start
//
//Input Data
//Accept N clients' data: each entry has a key (e.g., name or ID) and a telephone number.
//
//Choose Hash Function
//Select a suitable hash function, e.g., h(key) = key % table_size.
//
//Insert Data into Hash Table (Chaining Without Replacement)
//
//If collision occurs, append to the linked list at that index.
//
//Maintain a count of comparisons during insertion.
//
//Insert Data into Hash Table (Chaining With Replacement)
//
//If collision occurs and existing entry doesn’t belong to that index, swap and reinsert.
//
//Maintain a count of comparisons during insertion.
//
//Search for a Set of Keys (Same for Both Techniques)
//
//Search a set of M telephone numbers (by key).
//
//Record number of comparisons required for each technique.
//
//Compare Both Techniques
//
//Compare number of comparisons for lookup.
//
//Output performance statistics.
//
//End
