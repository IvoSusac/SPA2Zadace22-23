#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> intPair;

struct DisjointSet {
    vector<int> parent;
    vector<int> rank;
    int n;

    DisjointSet(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1);
        this->n = n;
        for (int i = 0; i <= n; ++i) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int FIND_SET(int u) {
        if (u != parent[u])
            parent[u] = FIND_SET(parent[u]);
        return parent[u];
    }

    void UNION(int x, int y) {
        x = FIND_SET(x), y = FIND_SET(y);

        if (rank[x] > rank[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rank[x] == rank[y])
            rank[y]++;
    }
};

class Graph
{
private:
    vector<vector<int>> AMatrix;

    int totalWeightOfGraph(vector<vector<int>> adjMatrix)
    {
        int sum = 0, n = adjMatrix.size();

        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                    sum += adjMatrix[i][j];
        
        return sum;
    }

    void printGraph(vector<vector<int>> adjMatrix)
    {
        int n = adjMatrix.size();

        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                if (adjMatrix[i][j] != 0) {
                    cout << i << " - " << j << " (" << adjMatrix[i][j] << ")";
                    cout << endl;
                }
            }
                    
    }
    
    // mjesto za pomoćne funkcije za algoritme

    int minKey(vector<int> key, vector<bool> mstSet) {
        int min = INT_MAX;
        int min_index;

        for (int i = 0; i < AMatrix.size(); ++i)
            if (!mstSet[i] && key[i] < min)
                min = key[i], min_index = i;
        
        return min_index;
    }

public:

    //konstruktor, paziti na kopiranje
    Graph(vector<vector<int>> adjMatrix)
    {
        int n = adjMatrix.size();

        AMatrix.resize(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                AMatrix[i][j] = adjMatrix[i][j];
    }

    int GraphWeight()
    {
        return this->totalWeightOfGraph(AMatrix);
    }

    void print()
    {
        this->printGraph(AMatrix);
    }

    Graph primMST(Graph G)
    {

        int V = G.AMatrix.size();

        vector<int> parent(V, 0);
        vector<int> key(V, 0);

        vector<bool> mstSet(V, false);

        for (int i = 0; i < V; ++i)
            key[i] = INT_MAX, mstSet[i] = false;
        
        key[0] = 0;

        parent[0] = -1;

        for (int i = 0; i < V - 1; ++i) {
            int u = minKey(key, mstSet);

            mstSet[u] = true;

            for (int v = 0; v < V; ++v) {
                if (G.AMatrix[u][v] != 0 && !mstSet[v] && G.AMatrix[u][v] < key[v])
                    parent[v] = u, key[v] = G.AMatrix[u][v];
            }
        }

        vector<vector<int>> matrix(V, vector<int>(V, 0));

        for (int i = 1; i < V; ++i)
            matrix[parent[i]][i] = G.AMatrix[i][parent[i]];
        
        return Graph(matrix);
    }

    Graph kruskalMST(Graph G)
    {
        int V = G.AMatrix.size();

        vector<pair<intPair, int>> edges;

        for (int i = 0; i < V; ++i)
            for (int j = i + 1; j < V; ++j) {
                if (G.AMatrix[i][j] != 0) {
                    edges.push_back({{i, j}, G.AMatrix[i][j]});
                }
            }

        sort(edges.begin(), edges.end(), [](const pair<intPair, int>& a, const pair<intPair, int>& b){ return a.second < b.second; });

        DisjointSet ds(V);

        vector<vector<int>> matrix(V, vector<int>(V, 0));

        vector<pair<intPair, int>>::iterator it;
        for(it = edges.begin(); it != edges.end(); ++it) {
            int u = it->first.first;
            int v = it->first.second;

            int set_u = ds.FIND_SET(u);
            int set_v = ds.FIND_SET(v);

            if (set_u != set_v) {
                matrix[u][v] = it->second;
            }

            ds.UNION(set_u, set_v);
        }

        return Graph(matrix);
    }


};

int main()
{
    //ovdje pretvoriti input u dvodimenzionalnu matricu i proslijediti konstruktoru
    //paziti na izgled matrice
    int n, k, l, r, w;
    cin >> n >> k;

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < k; ++i) {
        cin >> l >> r >> w;
        matrix[l][r] = w;
        matrix[r][l] = w;
    }

    /*
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    */

    Graph G(matrix);

    G.print();
    cout << "Total weight of G: " << G.GraphWeight() << endl << endl;

    Graph MST1 = G.primMST(G);
    cout << "MST with Prim's algorithm:" << endl;
    MST1.print();
    cout << "Total weight of MST with Prim: " << MST1.GraphWeight() << endl << endl;

    Graph MST2 = G.kruskalMST(G);
    cout << "MST with Kruskal's algorithm: " << endl;
    MST2.print();
    cout << "Total weight of MST with Kruskal: " << MST2.GraphWeight();

    return 0;
}