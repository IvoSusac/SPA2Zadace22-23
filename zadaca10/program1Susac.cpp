#include <iostream>
#include <vector>
#include <algorithm>

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
                    cout << i << " - " << j << endl; 
    }

    void findBridgesDFS(int start, vector<bool>& visited, vector<int>& discoveryTime, vector<int>& lowestDiscoveryTime, int parent, vector<pair<int, int>>& bridges) {
        static int time = 0;
        visited[start] = true; // posjecujemo prvi vrh u grafu
        discoveryTime[start] = lowestDiscoveryTime[start] = ++time; // inicijalizacija vremena otkrivanja za prvi vrh
        int n = AMatrix.size();

        for (int v = 0; v < n; ++v) {
            if (AMatrix[start][v]) {
                if (v == parent)
                    continue;
            
                if (visited[v])
                    lowestDiscoveryTime[start] = min(lowestDiscoveryTime[start], discoveryTime[v]);

                else {
                    parent = start;
                    findBridgesDFS(v, visited, discoveryTime, lowestDiscoveryTime, parent, bridges);

                    // updateamo lowest od start jer je moguce da postoji veza izmedu start i nasljednika od v
                    lowestDiscoveryTime[start] = min(lowestDiscoveryTime[start], lowestDiscoveryTime[v]);

                    if (lowestDiscoveryTime[v] > discoveryTime[start]) // ako je najmanje vrijeme za discoveranje v vece od discovery timea od start znaci da se u v moze samo doci kroz start, pa je to most
                        bridges.push_back({start, v});

                }
            }
        }
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

    void printBridges() {
        int n = AMatrix.size();

        vector<bool> visited(n, false);
        vector<int> discoveryTime(n, -1);
        vector<int> lowestDiscoveryTime(n, -1);
        int parent = -1;
        vector<pair<int, int>> bridges;

        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                findBridgesDFS(i, visited, discoveryTime, lowestDiscoveryTime, parent, bridges);
        }

        cout << bridges.size() << " kriticne veze" << endl;
    
        sort(bridges.begin(), bridges.end(), [](const pair<int, int>& p1, const pair<int, int> &p2){ return p1.first < p2.first; });
    
        for (auto p : bridges)
            cout << p.first << " - " << p.second << endl;
    }
};

int main()
{
    int n, k, l, r, temp;
    cin >> n >> k;

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < k; ++i) {
        cin >> l >> r >> temp;
        matrix[l][r] = 1;
        matrix[r][l] = 1;
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

   G.printBridges();

   return 0;
}