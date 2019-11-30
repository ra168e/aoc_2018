#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input;
    string line;
    input.open("input2.txt");
    unsigned index = 0;
    int charlist[29] = {0};
    unsigned twos, threes = 0;
    vector<string> strlist;
    if (input.is_open()) {
        while ( getline (input, line) ) {
            strlist.push_back(line);
            for(char& c:line) {
                index = (int) c - (int) 'a';
                charlist[index]++;
            }
            bool hastwo = false;
            bool hasthree = false;
            for(int i:charlist) {
                if(i == 2 && !hastwo) {
                    twos++;
                    hastwo = true;
                }
                if(i == 3 && !hasthree) {
                    threes++;
                    hasthree = true;
                }
            }
            memset(charlist, 0, sizeof(charlist));
        }
    }
    cout << "twos: " << twos << endl;
    cout << "threes: " << threes << endl;
    cout << "checksum: " << twos * threes << endl;
    unsigned diffcount;
    unsigned diffindex = 0;
    string result;
    // PART 2
    for(int i = 0; i < strlist.size(); i++) {
        vector<string> copy(strlist);
        copy.erase(copy.begin() + i);
        for(string s:copy) {
            diffcount = 0;
            for (int k = 0; k < s.length(); k++) {
                if (strlist[i][k] != s[k]) {
                    diffcount++;
                    diffindex = k;
                }    
            }
            if (diffcount == 1) {
                s.erase(s.begin() + diffindex);
                result = s;
            }
        }
    }
    cout << "sames: " << result << endl;
}
