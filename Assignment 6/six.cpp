#include <bits/stdc++.h>
using namespace std;
// Structure to represent an item
struct Item {
string name;
int weight;
int utility; // Importance or value
bool perishable; // Priority items
};
// 0/1 Knapsack using Dynamic Programming
pair<int, vector<int>> knapsackDP(vector<Item> &items, int W) {
int N = items.size();
vector<vector<int>> dp(N+1, vector<int>(W+1, 0));
// Build DP table
for(int i=1; i<=N; i++) {
for(int w=0; w<=W; w++) {
if(items[i-1].weight <= w) {
dp[i][w] = max(dp[i-1][w], dp[i-1][w - items[i-1].weight] + items[i-1].utility);
} else {
dp[i][w] = dp[i-1][w];
}
}
}
// Reconstruct chosen items
vector<int> selectedItems;
int w = W;
for(int i=N; i>0; i--) {
if(dp[i][w] != dp[i-1][w]) {
selectedItems.push_back(i-1);
w -= items[i-1].weight;
}
}
reverse(selectedItems.begin(), selectedItems.end());
return {dp[N][W], selectedItems};
}
// Greedy approach (approximation) based on utility/weight ratio
vector<int> knapsackGreedy(vector<Item> &items, int W) {

6

int N = items.size();
vector<pair<double, int>> ratioIndex;
for(int i=0; i<N; i++)
ratioIndex.push_back({(double)items[i].utility/items[i].weight, i});
sort(ratioIndex.rbegin(), ratioIndex.rend());
int totalWeight = 0;
vector<int> selectedItems;
for(auto &ri : ratioIndex) {
int idx = ri.second;
if(totalWeight + items[idx].weight <= W) {
selectedItems.push_back(idx);
totalWeight += items[idx].weight;
}
}
return selectedItems;
}
int main() {
int W; // Maximum truck capacity
cout << "Enter truck capacity (kg): ";
cin >> W;
int N; // Number of items
cout << "Enter number of items: ";
cin >> N;
vector<Item> items(N);
cout << "Enter item details (name weight utility perishable(0/1)):\n";
for(int i=0; i<N; i++) {
cin >> items[i].name >> items[i].weight >> items[i].utility >> items[i].perishable;
}
// Prioritize perishable items by artificially increasing their utility
for(auto &it : items) {
if(it.perishable) it.utility += 10; // priority bonus
}
// Solve using Dynamic Programming
auto result = knapsackDP(items, W);
cout << "\n=== Dynamic Programming Solution ===\n";
cout << "Maximum utility: " << result.first << endl;
cout << "Selected items:\n";

7

for(int idx : result.second)
cout << "- " << items[idx].name << " (Weight: " << items[idx].weight << ", Utility: " <<
items[idx].utility << ")\n";
// Solve using Greedy approximation
auto greedyItems = knapsackGreedy(items, W);
int greedyUtility = 0;
for(int idx : greedyItems) greedyUtility += items[idx].utility;
cout << "\n=== Greedy Approximation Solution ===\n";
cout << "Total utility: " << greedyUtility << endl;
cout << "Selected items:\n";
for(int idx : greedyItems)
cout << "- " << items[idx].name << " (Weight: " << items[idx].weight << ", Utility: " <<
items[idx].utility << ")\n";
return 0;
}
