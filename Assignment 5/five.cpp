#include <bits/stdc++.h>
using namespace std;
// Define a structure for edges
struct Edge {
int to;
double cost; // Can represent time, distance, or fuel cost
};
// Multistage Graph class
class MultistageGraph {
public:
int stages;
vector<vector<vector<Edge>>> graph; // graph[stage][node] = list of edges
MultistageGraph(int s) {
stages = s;
graph.resize(stages);
}
void addNode(int stage, int nodeCount) {
graph[stage].resize(nodeCount);
}
void addEdge(int stage, int fromNode, int toNode, double cost) {
graph[stage][fromNode].push_back({toNode, cost});
}

// Dynamic Programming to find minimum cost from source (stage 0) to last stage
pair<double, vector<int>> findOptimalRoute() {
int lastStage = stages - 1;
vector<vector<double>> dp(stages);
vector<vector<int>> nextNode(stages);
// Initialize DP tables
for(int i=0; i<stages; i++) {
int nodes = graph[i].size();
dp[i].resize(nodes, DBL_MAX);
nextNode[i].resize(nodes, -1);
}
// Base case: cost at last stage nodes = 0
for(int i=0; i<graph[lastStage].size(); i++) dp[lastStage][i] = 0;
// DP computation from second-last stage to first stage
for(int stage = lastStage - 1; stage >= 0; stage--) {
for(int u = 0; u < graph[stage].size(); u++) {
for(auto &e : graph[stage][u]) {
double cost = e.cost + dp[stage + 1][e.to];
if(cost < dp[stage][u]) {
dp[stage][u] = cost;
nextNode[stage][u] = e.to;
}
}
}
}
// Reconstruct path from stage 0, node 0
vector<int> path;
int currentNode = 0;
path.push_back(currentNode);
for(int stage = 0; stage < stages - 1; stage++) {
currentNode = nextNode[stage][currentNode];
path.push_back(currentNode);
}
return {dp[0][0], path};
}
};
int main() {
// Example: 3-stage network

int stages = 3;
MultistageGraph graph(stages);
// Adding nodes per stage
graph.addNode(0, 2); // Stage 0 has 2 nodes
graph.addNode(1, 3); // Stage 1 has 3 nodes
graph.addNode(2, 2); // Stage 2 has 2 nodes
// Adding edges (fromStage -> toStage)
// Stage 0 -> Stage 1
graph.addEdge(0, 0, 0, 4);
graph.addEdge(0, 0, 1, 2);
graph.addEdge(0, 1, 1, 1);
graph.addEdge(0, 1, 2, 5);
// Stage 1 -> Stage 2
graph.addEdge(1, 0, 0, 3);
graph.addEdge(1, 1, 0, 2);
graph.addEdge(1, 1, 1, 3);
graph.addEdge(1, 2, 1, 2);
// Compute optimal route
auto result = graph.findOptimalRoute();
double minCost = result.first;
vector<int> path = result.second;
cout << "Optimal delivery route:\n";
for(int stage=0; stage<path.size(); stage++)
cout << "Stage " << stage << " Node " << path[stage] << " -> ";
cout << "END\n";
cout << "Minimum cost: " << minCost << endl;
return 0;
}
