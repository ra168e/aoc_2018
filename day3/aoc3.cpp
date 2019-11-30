#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

typedef struct {
    unsigned ID;
    unsigned xy[2];
    unsigned wh[2];
} points_t;

int main() {
    ifstream input;
    string line;
    input.open("input3.txt");
    vector<points_t> pointlist;
    if (input.is_open()) {
        while ( getline (input, line) ) {
            // Convert all this to regex
            points_t pt;
            int idloc = line.find(" ", 0);
            pt.ID = atoi(line.substr(1, idloc).c_str());
            size_t xbegin = line.find(" ", line.find("@", idloc)) + 1;
            size_t xend = line.find(",", xbegin);
            pt.xy[0] = atoi(line.substr(xbegin, xend).c_str());
            size_t ybegin = xend + 1;
            size_t yend = line.find(":", xend);
            pt.xy[1] = atoi(line.substr(ybegin, yend).c_str());
            size_t wbegin = line.find(" ", yend) + 1;
            size_t wend = line.find("x", wbegin);
            pt.wh[0] = atoi(line.substr(wbegin, wend).c_str());
            size_t hbegin = wend + 1;
            size_t hend = line.size();
            pt.wh[1] = atoi(line.substr(hbegin, hend).c_str());
            pointlist.push_back(pt);
        }
    }
    int grid[1000][1000] = {0};
    for (points_t pt:pointlist) {
        for (int i = 0; i < pt.wh[0]; i++) {
            for (int j = 0; j < pt.wh[1]; j++) {
                grid[pt.xy[0] + i][pt.xy[1] + j]++;
            }
        }
    }
    int used = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (grid[i][j] > 1) {
                used ++;
            }
        }
    }
    cout << used << " square inches used multiple times" << endl;
    // PART 2
    unsigned area = 0;
    unsigned ID;
    for (points_t pt:pointlist) {
        for (int i = 0; i < pt.wh[0]; i++) {
            for (int j = 0; j < pt.wh[1]; j++) {
                area += grid[pt.xy[0] + i][pt.xy[1] + j];
            }
        }
        if (area == (pt.wh[0] * pt.wh[1])) {
            ID = pt.ID;
        }
        area = 0;
    }
    cout << "ID of non-overlapping patch: " << to_string(ID) << endl; 
}
 
