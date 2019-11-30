#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream input;
    string line;
    int result = 0;
    int count = 0;
    input.open("input.txt");
    int *acc = nullptr;
    if (input.is_open()) {
        while ( getline (input, line) ) {
            result += stod(line);
            count++;
        }
        input.clear();
        input.seekg(0, ios::beg);
        acc = (int *) malloc(count * sizeof(double));
        for ( int i = 0; i < count; i++ ) {
            getline (input, line);
            acc[i] = stoi(line);
        }
        input.close();
    }
    vector<int> accv;
    int freq = 0;
    int found = 0;
    int iter = 0;
    while (found == 0) {
        for (int i = 0; i < count; i++) {
            freq += acc[i];
            if (find(accv.begin(), accv.end(), freq) != accv.end()) {
                found = i;
                break;
            }
            accv.push_back(freq);
            iter++;
        }
        cout << iter << endl;
    }
    cout << "Frequency: " << result << endl;
    cout << "First repeat: " << found << endl;
    cout << "Iter: " << iter << endl;
    free(acc);
}
