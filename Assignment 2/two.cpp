#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;
struct Movie {
string title;
double imdbRating;
int releaseYear;
int popularity;
};
// Function to read movie data from CSV file
bool readMoviesFromCSV(const string &filename, vector<Movie> &movies) {
ifstream file(filename);
if (!file.is_open()) {
cerr << " Error: Could not open file " << filename << endl;
return false;
}
string line;
getline(file, line); // skip header line
while (getline(file, line)) {
stringstream ss(line);
Movie m;
string rating, year, pop;
getline(ss, m.title, ',');
getline(ss, rating, ',');
getline(ss, year, ',');
getline(ss, pop, ',');
try {

m.imdbRating = stod(rating);
m.releaseYear = stoi(year);
m.popularity = stoi(pop);
movies.push_back(m);
} catch (...) {
cerr << "Skipping invalid line: " << line << endl;
}
}
file.close();
return true;
}
// Swap helper
void swap(Movie &a, Movie &b) {
Movie temp = a;
a = b;
b = temp;
}
// Partition function
int partition(vector<Movie> &movies, int low, int high, int choice) {
double pivotRating = movies[high].imdbRating;
int pivotYear = movies[high].releaseYear;
int pivotPopularity = movies[high].popularity;
int i = low - 1;
for (int j = low; j < high; j++) {
bool condition = false;
if (choice == 1)
condition = movies[j].imdbRating >= pivotRating;
else if (choice == 2)
condition = movies[j].releaseYear >= pivotYear;
else
condition = movies[j].popularity >= pivotPopularity;
if (condition) {
i++;
swap(movies[i], movies[j]);
}
}
swap(movies[i + 1], movies[high]);
return i + 1;
}
// QuickSort recursive function
void quickSort(vector<Movie> &movies, int low, int high, int choice) {
if (low < high) {
int pi = partition(movies, low, high, choice);
quickSort(movies, low, pi - 1, choice);
quickSort(movies, pi + 1, high, choice);
}
}
// Display top N movies
void displayTopMovies(const vector<Movie> &movies, int n) {
cout << "\nTop " << n << " Movies after sorting:\n";
cout << left << setw(25) << "Title"
<< setw(15) << "IMDB Rating"
<< setw(15) << "Year"
<< setw(15) << "Popularity" << endl;

cout << string(70, '-') << endl;
for (int i = 0; i < n && i < (int)movies.size(); i++) {
cout << left << setw(25) << movies[i].title
<< setw(15) << movies[i].imdbRating
<< setw(15) << movies[i].releaseYear
<< setw(15) << movies[i].popularity << endl;
}
}
int main() {
vector<Movie> movies;
string filename = "movies.csv";
cout << " Reading data from " << filename << "..." << endl;
if (!readMoviesFromCSV(filename, movies)) {
return 1;
}
cout << " Successfully loaded " << movies.size() << " movies.\n";
cout << "\nSort movies based on:\n";
cout << "1. IMDB Rating\n";
cout << "2. Release Year\n";
cout << "3. Watch Time Popularity\n";
cout << "Enter your choice: ";
int choice;
cin >> choice;
cout << "\n Sorting movies using QuickSort...\n";
auto start = high_resolution_clock::now();
quickSort(movies, 0, movies.size() - 1, choice);
auto end = high_resolution_clock::now();
duration<double> elapsed = end - start;
cout << " Sorting completed in " << fixed << setprecision(4)
<< elapsed.count() << " seconds.\n";
displayTopMovies(movies, 10);
return 0;
}
