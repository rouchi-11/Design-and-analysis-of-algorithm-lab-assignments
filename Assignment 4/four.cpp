#include <bits/stdc++.h>
using namespace std;
struct Edge {
int to;
int weight;
};
void dijkstra(int source, vector<vector<Edge>> &graph, vector<int> &dist, vector<int> &parent) {
int V = graph.size();
dist.assign(V, INT_MAX);
parent.assign(V, -1);
dist[source] = 0;
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
pq.push({0, source});
while (!pq.empty()) {
int u = pq.top().second;
int d = pq.top().first;
pq.pop();
if (d > dist[u]) continue;
for (auto &edge : graph[u]) {
int v = edge.to;
int w = edge.weight;
if (dist[v] > dist[u] + w) {
dist[v] = dist[u] + w;
parent[v] = u;
pq.push({dist[v], v});
}
}
}
}
// Update the weight of an edge in an undirected graph
void updateWeight(vector<vector<Edge>> &graph, int u, int v, int newWeight) {
for (auto &edge : graph[u]) {

9

if (edge.to == v) {
edge.weight = newWeight;
break;
}
}
for (auto &edge : graph[v]) {
if (edge.to == u) {
edge.weight = newWeight;
break;
}
}
}
// Reconstruct path from source to destination
vector<int> reconstructPath(int source, int dest, const vector<int> &parent) {
vector<int> path;
for (int cur = dest; cur != -1; cur = parent[cur]) {
path.push_back(cur);
}
reverse(path.begin(), path.end());
if (path.front() == source)
return path;
else
return {}; // No path found
}
int main() {
int V, E;
cout << "Enter number of intersections (vertices): ";
cin >> V;
cout << "Enter number of roads (edges): ";
cin >> E;
vector<vector<Edge>> graph(V);
cout << "Enter edges (u v w):\n";
for (int i = 0; i < E; i++) {
int u, v, w;
cin >> u >> v >> w;
graph[u].push_back({v, w});
graph[v].push_back({u, w}); // undirected road
}
int source;
cout << "Enter ambulance start location (source): ";
cin >> source;
int H;

10

cout << "Enter number of hospitals: ";
cin >> H;
vector<int> hospitals(H);
cout << "Enter hospital nodes: ";
for (int i = 0; i < H; i++) {
cin >> hospitals[i];
}
vector<int> dist, parent;
dijkstra(source, graph, dist, parent);
int minTime = INT_MAX, nearestHospital = -1;
for (int h : hospitals) {
if (dist[h] < minTime) {
minTime = dist[h];
nearestHospital = h;
}
}
if (nearestHospital == -1) {
cout << "No hospital reachable.\n";
} else {
cout << "Nearest hospital is at node " << nearestHospital
<< " with travel time " << minTime << " minutes.\n";
vector<int> path = reconstructPath(source, nearestHospital, parent);
cout << "Optimal path: ";
for (int node : path) {
cout << node;
if (node != path.back()) cout << " -> ";
}
cout << "\n";
}
// Example of dynamic updates:
char choice;
while (true) {
cout << "Do you want to update traffic conditions? (y/n): ";
cin >> choice;
if (choice != 'y' && choice != 'Y') break;
int u, v, w;
cout << "Enter edge to update (u v) and new travel time w: ";
cin >> u >> v >> w;
updateWeight(graph, u, v, w);
// Recalculate shortest path after update
dijkstra(source, graph, dist, parent);

11

minTime = INT_MAX; nearestHospital = -1;
for (int h : hospitals) {
if (dist[h] < minTime) {
minTime = dist[h];
nearestHospital = h;
}
}
if (nearestHospital == -1) {
cout << "No hospital reachable after update.\n";
} else {
cout << "After update, nearest hospital: node " << nearestHospital
<< " with travel time " << minTime << " minutes.\n";
vector<int> path = reconstructPath(source, nearestHospital, parent);
cout << "New optimal path: ";
for (int node : path) {
cout << node;
if (node != path.back()) cout << " -> ";
}
cout << "\n";
}
}
return 0;
}
