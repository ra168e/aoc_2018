#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <numeric>
#include <algorithm>
#include <climits>

using namespace std;

string read_line(string filename)
{
    ifstream input;
    input.open(filename);
    string line;

    if (input.is_open())
    {
        // Assuming we have just one line
        getline(input, line);
    }
    return line;
}

string reduce(string line)
{
    string out, newline;
    newline = line;
    out = line;
    for (int i = 1; i < line.length(); i++)
    {
        if (toupper(line[i - 1]) == toupper(line[i]) && abs(line[i -1] - line[i]) == 32)
        {
            newline.erase(i-1, 2);
            out = reduce(newline);
            break;
        }
    }
    return out;
}

int min_lengths(string reduced)
{
    char chrange[26];
    iota(chrange, chrange + 26, 'a');
    int min_len = INT_MAX;
    for (const char& c: chrange)
    {
       string temp(reduced.begin(), reduced.end());
       temp.erase(remove(temp.begin(), temp.end(), c), temp.end());
       temp.erase(remove(temp.begin(), temp.end(), char(c - 32)), temp.end());
       int current = reduce(temp).length();
       if (current < min_len)
       {
           min_len = current;
       }
    }
    return min_len;
}

int main()
{
    string example = read_line("input5.txt");
    cout << "part 1: " << reduce(example).length() << endl;
    cout << "part 2: " << min_lengths(example) << endl;
}


