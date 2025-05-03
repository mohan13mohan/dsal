#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Edge structure
struct Edge {
    int src, dest, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set Union (Union-Find)
class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int xr = find(x);
        int yr = find(y);
        if (xr == yr) return false;

        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};

// Kruskal’s Algorithm
int kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(V);

    int mstCost = 0;
    vector<Edge> mstEdges;

    for (const Edge& e : edges) {
        if (dsu.unite(e.src, e.dest)) {
            mstCost += e.weight;
            mstEdges.push_back(e);
        }
    }

    cout << "\nEdges in the Minimum Spanning Tree:\n";
    for (const Edge& e : mstEdges)
        cout << e.src + 1 << " - " << e.dest + 1 << " : " << e.weight << endl;

    return mstCost;
}

int main() {
    int V;
    cout << "Enter number of offices: ";
    cin >> V;

    vector<Edge> edges;
    char choice;
    int weight;

    // Ask for each pair (i, j)
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            cout << "Do you want a connection between office " << i + 1 << " and " << j + 1 << "? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << "Enter weight (cost) of connection: ";
                cin >> weight;
                edges.push_back({i, j, weight});
            }
        }
    }

    int totalCost = kruskalMST(V, edges);
    cout << "\nTotal cost to connect all offices: " << totalCost << endl;

    return 0;
}





// output:-



// Enter number of offices: 4
// Do you want a connection between office 1 and 2? (y/n): y
// Enter weight (cost) of connection: 5
// Do you want a connection between office 1 and 3? (y/n): y
// Enter weight (cost) of connection: 6
// Do you want a connection between office 1 and 4? (y/n): y
// Enter weight (cost) of connection: 8
// Do you want a connection between office 2 and 3? (y/n): y
// Enter weight (cost) of connection: 12
// Do you want a connection between office 2 and 4? (y/n): y
// Enter weight (cost) of connection: 23
// Do you want a connection between office 3 and 4? (y/n): n

// Edges in the Minimum Spanning Tree:
// 1 - 2 : 5
// 1 - 3 : 6
// 1 - 4 : 8

// Total cost to connect all offices: 19