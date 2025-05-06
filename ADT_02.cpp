#include <iostream>
#include <string.h>
using namespace std;

class HashFunction {
    typedef struct hash {
        long key;
        char name[10];
    } hash;

    hash h[10];

public:
    HashFunction();
    void insert();
    void display();
    int find(long);
    void Delete(long);
};

HashFunction::HashFunction() {
    for (int i = 0; i < 10; i++) {
        h[i].key = -1;
        strcpy(h[i].name, "NULL");
    }
}

void HashFunction::Delete(long k) {
    int index = find(k);
    if (index == -1) {
        cout << "Key Not Found" << endl;
    } else {
        h[index].key = -1;
        strcpy(h[index].name, "NULL");
        cout << "Key is Deleted" << endl;
    }
}

int HashFunction::find(long k) {
    for (int i = 0; i < 10; i++) {
        if (h[i].key == k) {
            cout << h[i].key << " is Found at " << i << " Location With Name " << h[i].name << endl;
            return i;
        }
    }
    return -1;
}

void HashFunction::display() {
    cout << "Key\t\tName" << endl;
    for (int i = 0; i < 10; i++) {
        // HERE WE ARE USING \t MEANS "horizontal tab spaces"
        cout << "h[" << i << "]\t" << h[i].key << "\t\t" << h[i].name << endl;
    }
}

void HashFunction::insert() {
    char ans, n[10], ntemp[10];
    long k, temp;
    int v, hi, cnt = 0, flag = 0, i;

    do {
        if (cnt >= 10) {
            cout << "Hash Table is FULL" << endl;
            break;
        }

        cout << "Enter a Telephone No: ";
        cin >> k;
        cout << "Enter a Client Name: ";
        cin >> n;

        hi = k % 10;

        if (h[hi].key == -1) {
            h[hi].key = k;
            strcpy(h[hi].name, n);
        } else {
            if (h[hi].key % 10 != hi) {
                temp = h[hi].key;
                strcpy(ntemp, h[hi].name);
                h[hi].key = k;
                strcpy(h[hi].name, n);

                for (i = hi + 1; i < 10; i++) {
                    if (h[i].key == -1) {
                        h[i].key = temp;
                        strcpy(h[i].name, ntemp);
                        flag = 1;
                        break;
                    }
                }

                for (i = 0; i < hi && flag == 0; i++) {
                    if (h[i].key == -1) {
                        h[i].key = temp;
                        strcpy(h[i].name, ntemp);
                        break;
                    }
                }
            } else {
                for (i = hi + 1; i < 10; i++) {
                    if (h[i].key == -1) {
                        h[i].key = k;
                        strcpy(h[i].name, n);
                        flag = 1;
                        break;
                    }
                }

                for (i = 0; i < hi && flag == 0; i++) {
                    if (h[i].key == -1) {
                        h[i].key = k;
                        strcpy(h[i].name, n);
                        break;
                    }
                }
            }
        }

        flag = 0;
        cnt++;

        cout << ".....Do You Want to Insert More Key (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}

int main() {
    long k;
    int ch, index;
    char ans;
    HashFunction obj;

    do {
        cout << "***** Telephone Directory (ADT) *****" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Display" << endl;
        cout << "3. Find" << endl;
        cout << "4. Delete" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            obj.insert();
            break;
        case 2:
            obj.display();
            break;
        case 3:
            cout << "Enter a Key Which You Want to Search: ";
            cin >> k;
            index = obj.find(k);
            if (index == -1) {
                cout << "Key Not Found" << endl;
            }
            break;
        case 4:
            cout << "Enter a Key Which You Want to Delete: ";
            cin >> k;
            obj.Delete(k);
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice!" << endl;
        }

        cout << ".....Do You Want to Continue in Main Menu (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    return 0;
}



//output:-
//
//
//***** Telephone Directory (ADT) *****
//1. Insert
//2. Display
//3. Find
//4. Delete
//5. Exit
//Enter Your Choice: 1
//Enter a Telephone No: 8989
//Enter a Client Name: harsh
//.....Do You Want to Insert More Key (y/n): y
//Enter a Telephone No: 5656
//Enter a Client Name: jay
//.....Do You Want to Insert More Key (y/n): y
//Enter a Telephone No: 2323
//Enter a Client Name: gayan
//.....Do You Want to Insert More Key (y/n): n
//.....Do You Want to Continue in Main Menu (y/n): y
//***** Telephone Directory (ADT) *****
//1. Insert
//2. Display
//3. Find
//4. Delete
//5. Exit
//Enter Your Choice: 2
//Key             Name
//h[0]    -1              NULL
//h[1]    -1              NULL
//h[2]    -1              NULL
//h[3]    2323            gayan
//h[4]    -1              NULL
//h[5]    -1              NULL
//h[6]    5656            jay
//h[7]    -1              NULL
//h[8]    -1              NULL
//h[9]    8989            harsh
//.....Do You Want to Continue in Main Menu (y/n): y
//***** Telephone Directory (ADT) *****
//1. Insert
//2. Display
//3. Find
//4. Delete
//5. Exit
//Enter Your Choice: 3
//Enter a Key Which You Want to Search: 8989
//8989 is Found at 9 Location With Name harsh
//.....Do You Want to Continue in Main Menu (y/n): y
//***** Telephone Directory (ADT) *****
//1. Insert
//2. Display
//3. Find
//4. Delete
//5. Exit
//Enter Your Choice: 4
//Enter a Key Which You Want to Delete: 5656
//5656 is Found at 6 Location With Name jay
//Key is Deleted
//.....Do You Want to Continue in Main Menu (y/n): y
//***** Telephone Directory (ADT) *****
//1. Insert
//2. Display
//3. Find
//4. Delete
//5. Exit
//Enter Your Choice: 2
//Key             Name
//h[0]    -1              NULL
//h[1]    -1              NULL
//h[2]    -1              NULL
//h[3]    2323            gayan
//h[4]    -1              NULL
//h[5]    -1              NULL
//h[6]    -1              NULL
//h[7]    -1              NULL
//h[8]    -1              NULL
//h[9]    8989            harsh
//.....Do You Want to Continue in Main Menu (y/n):



//flowchat:-
//
//
//Start
//Begin the operation (Insert / Find / Delete).
//
//Input (key, value)
//Get the key (and value for insert).
//
//Compute Hash Index
//Use index = Hash(key), e.g., key % table_size.
//
//Check Collision
//Is the slot at index empty?
//
//If yes ? proceed to step 6.
//
//If no ? collision occurred ? step 5.
//
//Handle Collision
//
//Without Replacement: Add the (key, value) to the linked list at index.
//
//With Replacement: If existing key at index doesn't belong there, swap and reinsert displaced key.
//
//Perform Operation
//
//Insert: Add key-value at correct position.
//
//Find: Search the list at index for key.
//
//Delete: Search and remove key from list.
//
//Return Result
//
//Return value (Find), success/failure (Insert/Delete).
//
//End
//Finish the operation.
