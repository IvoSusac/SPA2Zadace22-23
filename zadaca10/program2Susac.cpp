#include <iostream>
#include <vector>

using namespace std;

class Graph
{
private:
    vector<vector<int>> AMatrix;

    void printGraph(vector<vector<int>> adjMatrix)
    {
        int n = adjMatrix.size();
        
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if(adjMatrix[i][j] != 0)
                    cout << i << " - " << j << adjMatrix[i][j] << endl;
    }

    /*pair<int, int> minElement(vector<int> &d) {
        int min = d[0];
        int index = 0;

        for (int i = 1; i < d.size(); ++i) {
            if (d[i] < min) {
                min = d[i];
                index = i;
            }
        }

        return {min, index};
    }

    void relax(int u, int v, vector<int> &d) {
        if (d[v] > (d[u] + AMatrix[u][v]))
            d[v] = d[u] + AMatrix[u][v];
    }
    */

   int minDist(vector<int> dist, vector<bool> shortestPathTree) {
        int n = AMatrix.size();

        int min = INT_MAX; 
        int min_index;
  
        for (int v = 0; v < n; v++)
            if (shortestPathTree[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;
  
        return min_index;
    }
    
public:

    Graph(vector<vector<int>> &adjMatrix)
    {
		AMatrix = adjMatrix;
    }

    void print()
    {
        printGraph(AMatrix);
    }

    int dijkstra(int src, int dest) {
        int n = AMatrix.size();

        /*
        vector<int> d(n, INT_MAX);
        d[src] = 0;

        vector<pair<int, int>> S;

        vector<int> dcopy = d;

        while (d.size() > 0) {
            pair<int, int> minEl = minElement(dcopy);

            int u = minEl.first;

            S.push_back({u, minEl.second});

            for (int v = minEl.second; v < n; ++v) {
                if (AMatrix[minEl.second][v] != 0) {
                    relax(minEl.second, v, dcopy);
                }
            }

            d.erase(d.begin() + minEl.second);
            dcopy[minEl.second] = INT_MAX;
        }

        int solution = -1;

        for (auto p : S) {
            if (p.second == dest)
                solution = p.first;
        }

        return solution;
        */

       vector<int> dist(n, INT_MAX);
       vector<bool> shortestPathTree(n, false);

       dist[src] = 0;

       for (int i = 0; i < n - 1; ++i) {
            int u = minDist(dist, shortestPathTree);

            shortestPathTree[u] = true;

            for (int v = 0; v < n; ++v) {
                if (!shortestPathTree[v] && AMatrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + AMatrix[u][v] < dist[v])
                    dist[v] = dist[u] + AMatrix[u][v];
            }
       }

       return dist[dest];
    }
};

int main()
{
    int n, k, l, r, w, s, f;
    cin >> n >> k >> s >> f;

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < k; ++i) {
        cin >> l >> r >> w;
        matrix[l - 1][r - 1] = w + 12;
        matrix[r - 1][l - 1] = w + 12;
    }
    
    /*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    */

    Graph G(matrix);

    cout << G.dijkstra(s - 1, f - 1);
    return 0;
}