#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adjList;

public:
    Graph(int V) : V(V) {
        adjList.resize(V);
    }

    void addEdge(int u, int v, int w = 1) {
        adjList[u].emplace_back(v, w);
        adjList[v].emplace_back(u, w);
    }

    vector<int> dijkstra(int src, int dest) {
        vector<int> dist(V, INT_MAX);
        vector<int> prev(V, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[src] = 0;
        pq.emplace(0, src);

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const pair<int, int>& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                    prev[v] = u;
                }
            }
        }

        vector<int> path;
        for (int at = dest; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        return (path.front() == src) ? path : vector<int>{};
    }
};

int main() {
    int V = 57;
    Graph g(V);

    // Adding edges according to the given mapping
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.addEdge(8, 9);
    g.addEdge(8, 28);
    g.addEdge(9, 10);
    g.addEdge(10, 11);
    g.addEdge(11, 12);
    g.addEdge(12, 13);
    g.addEdge(13, 14);
    g.addEdge(14, 15);
    g.addEdge(15, 16);
    g.addEdge(16, 17);
    g.addEdge(17, 18);
    g.addEdge(17, 48);
    g.addEdge(17, 47);
    g.addEdge(18, 19);
    g.addEdge(19, 20);
    g.addEdge(20, 21);
    g.addEdge(21, 22);
    g.addEdge(22, 23);
    g.addEdge(23, 24);
    g.addEdge(24, 25);
    g.addEdge(25, 26);
    g.addEdge(26, 27);
    g.addEdge(56, 55);
    g.addEdge(55, 54);
    g.addEdge(54, 53);
    g.addEdge(53, 52);
    g.addEdge(52, 51);
    g.addEdge(51, 50);
    g.addEdge(50, 49);
    g.addEdge(49, 48);
    g.addEdge(48, 17);
    g.addEdge(17, 47);
    g.addEdge(47, 46);
    g.addEdge(46, 45);
    g.addEdge(45, 44);
    g.addEdge(44, 35);
    g.addEdge(35, 43);
    g.addEdge(43, 42);
    g.addEdge(42, 41);
    g.addEdge(41, 40);
    g.addEdge(40, 39);
    g.addEdge(39, 38);
    g.addEdge(38, 37);
    g.addEdge(37, 36);
    g.addEdge(35, 34);
    g.addEdge(34, 33);
    g.addEdge(33, 32);
    g.addEdge(32, 31);
    g.addEdge(31, 30);
    g.addEdge(30, 29);
    g.addEdge(29, 28);
    g.addEdge(28, 8);

    unordered_map<string, int> placeToNode = {
        {"", 0}, {"LBnagar", 1}, {"Victoria_memorial", 2}, {"chaitanyapuri", 3},
        {"Dilshukhnagar", 4}, {"moosrambagh", 5}, {"NewMarket", 6}, {"malakpet", 7},
        {"MGbusstation", 8}, {"Osmania_medical", 9}, {"Gandhibhavan", 10},
        {"Nampally", 11}, {"Assembly", 12}, {"Lakdikapool", 13}, {"Khairtabad", 14},
        {"Irrummanzil", 15}, {"Panjagutta", 16}, {"Ameerpet", 17}, {"SRnagar", 18},
        {"ESIhospital", 19}, {"Erragadda", 20}, {"Bharatnagar", 21}, {"Moosapet", 22},
        {"DR_BRambedkar", 23}, {"Kukatpally", 24}, {"KPHBcolony", 25}, {"JNTUcollege", 26},
        {"Miyapur", 27}, {"Sultanbazar", 28}, {"Narayanguda", 29}, {"Chikkadpali", 30},
        {"RTCxroads", 31}, {"Musheerabad", 32}, {"Gandhihospital", 33},
        {"Secunderabad West", 34}, {"Paradeground", 35}, {"Nagole", 36},
        {"Uppal", 37}, {"stadium", 38}, {"NGRI", 39}, {"Habsiguda", 40},
        {"Tarnaka", 41}, {"Mettuguda", 42}, {"Secunderabad East", 43},
        {"Paradise", 44}, {"Rasoolpura", 45}, {"PrakashNagar", 46},
        {"Begumpet", 47}, {"MathuraNagar", 48}, {"Yusufguda", 49},
        {"Jubliehills", 50}, {"JH-checkpost", 51}, {"Peddamagudi", 52},
        {"Madhapur", 53}, {"Dugamcheruvu", 54}, {"Hitechcity", 55}, {"raidurg", 56}
    };

    unordered_map<int, string> nodeToPlace;
    for (const auto& pair : placeToNode) {
        nodeToPlace[pair.second] = pair.first;
    }

    string sourcePlace, destinationPlace;
    cout << "Enter source place: ";
    getline(cin, sourcePlace);
    cout << "Enter destination place: ";
    getline(cin, destinationPlace);

    int srcNode = placeToNode[sourcePlace];
    int destNode = placeToNode[destinationPlace];

    vector<int> path = g.dijkstra(srcNode, destNode);

    if (path.empty()) {
        cout << "No path found from " << sourcePlace << " to " << destinationPlace << endl;
    } else {
        cout << "Shortest path from " << sourcePlace << " to " << destinationPlace << ":\n";
        cout << setw(5) << left << "No." << setw(20) << "Station" << "\n";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << setw(5) << i + 1 << setw(20) << nodeToPlace[path[i]] << "\n";
        }
    }

    return 0;
}
