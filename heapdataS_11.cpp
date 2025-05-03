#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, mark;
    vector<int> marks;

    cout << "Enter number of students: ";
    cin >> n;

    cout << "Enter marks of " << n << " students:\n";
    for (int i = 0; i < n; ++i) {
        cin >> mark;
        marks.push_back(mark);
    }

    // Max-Heap for finding maximum
    priority_queue<int> maxHeap(marks.begin(), marks.end());

    // Min-Heap for finding minimum
    priority_queue<int, vector<int>, greater<int>> minHeap(marks.begin(), marks.end());

    cout << "\nMaximum Marks: " << maxHeap.top() << endl;
    cout << "Minimum Marks: " << minHeap.top() << endl;

    return 0;
}


// output:-

// Enter number of students: 5
// Enter marks of 5 students:
// 10
// 5
// 84
// 65
// 22

// Maximum Marks: 84
// Minimum Marks: 5