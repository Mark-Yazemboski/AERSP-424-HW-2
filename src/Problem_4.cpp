#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include <matplot/matplot.h>
using namespace std;

int main() {
    // Vectors to hold x, y, and time values
    std::cout << "Current Working Directory: "
        << std::filesystem::current_path() << std::endl;
    vector<double> x, y, time;

    // Open the CSV file
    cout << "HI" << endl;
    ifstream file("polar_data.csv");
    if (!file.is_open()) {
        cerr << "Error: Failed to open file 'polar_data.csv'. Make sure the file exists in the correct directory." << endl;
        return 1;
    }
    cout << "HI2" << endl;

    // Read and parse the CSV file
    string line;
    cout << "HI3" << endl;
    while (getline(file, line)) {
        cout << "Reading line: " << line << endl; // Debug: Print the line being read
        stringstream ss(line);
        string value;
        vector<double> row;

        // Split the line by commas
        while (getline(ss, value, ',')) {
            try {
                row.push_back(stod(value));
            }
            catch (const invalid_argument& e) {
                cerr << "Error: Invalid data found in file. Could not convert to double: " << value << endl;
                return 1;
            }
        }

        // Add to respective vectors
        if (row.size() == 3) {
            x.push_back(row[0]);
            y.push_back(row[1]);
            time.push_back(row[2]);
        }
        else {
            cerr << "Warning: Line does not have exactly 3 values. Skipping this line." << endl;
        }
    }

    cout << "File read successfully!" << endl;

    // Output size of vectors for verification
    cout << "Number of points read: " << x.size() << endl;
    file.close();

    // Debugging: Print the size of the data vectors
    std::cout << "Read " << x.size() << " data points." << std::endl;

    // Plot the data using Matplot++
    matplot::plot(x, y);
    matplot::title("Polar Plot");
    matplot::xlabel("x");
    matplot::ylabel("y");
    matplot::show();

    return 0;
}
