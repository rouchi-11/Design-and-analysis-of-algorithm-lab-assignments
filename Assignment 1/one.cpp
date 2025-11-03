#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;
struct Order {
string orderID;
time_t timestamp;
};
// Function to generate random orders
void generateSampleOrders(vector<Order>& orders, int n) {
tm base_time = {};
base_time.tm_year = 2025 - 1900;
base_time.tm_mon = 5; // June (0-based)
base_time.tm_mday = 24;
base_time.tm_hour = 12;
time_t base = mktime(&base_time);
srand(static_cast<unsigned int>(time(nullptr)));
for (int i = 0; i < n; i++) {
int random_minutes = rand() % 100000; // up to ~70 days
orders[i].timestamp = base + (random_minutes * 60);
orders[i].orderID = "ORD" + to_string(i + 1);
}
}
// Merge function for merge sort
void merge(vector<Order>& orders, int left, int mid, int right) {
int n1 = mid - left + 1;
int n2 = right - mid;
vector<Order> L(n1), R(n2);
for (int i = 0; i < n1; i++) L[i] = orders[left + i];
for (int j = 0; j < n2; j++) R[j] = orders[mid + 1 + j];
int i = 0, j = 0, k = left;
while (i < n1 && j < n2) {
if (L[i].timestamp <= R[j].timestamp)
orders[k++] = L[i++];

else
orders[k++] = R[j++];
}
while (i < n1) orders[k++] = L[i++];
while (j < n2) orders[k++] = R[j++];
}
// Recursive merge sort
void mergeSort(vector<Order>& orders, int left, int right) {
if (left < right) {
int mid = left + (right - left) / 2;
mergeSort(orders, left, mid);
mergeSort(orders, mid + 1, right);
merge(orders, left, mid, right);
}
}
// Print first N orders
void printFirstNOrders(const vector<Order>& orders, int n) {
char buffer[80];
for (int i = 0; i < n && i < (int)orders.size(); i++) {
tm* timeinfo = gmtime(&orders[i].timestamp);
strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", timeinfo);
cout << "Order ID: " << orders[i].orderID
<< ", Timestamp: " << buffer << endl;
}
}
int main() {
const int NUM_ORDERS = 1000000; // Try smaller numbers like 1000 for testing
vector<Order> orders(NUM_ORDERS);
cout << "Generating orders..." << endl;
generateSampleOrders(orders, NUM_ORDERS);
cout << "Sorting orders by timestamp..." << endl;
auto start = high_resolution_clock::now();
mergeSort(orders, 0, NUM_ORDERS - 1);
auto end = high_resolution_clock::now();
duration<double> elapsed = end - start;
cout << "Done! Sorted " << NUM_ORDERS
<< " orders in " << fixed << setprecision(2)
<< elapsed.count() << " seconds.\n" << endl;
cout << "First 10 Sorted Orders:\n";

printFirstNOrders(orders, 10);
return 0;
}
