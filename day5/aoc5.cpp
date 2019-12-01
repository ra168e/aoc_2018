#include <iostream>
#include <fstream>
#include <stdlib.h>

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

int main()
{
    string example = read_line("input5.txt");
    cout << reduce(example).length() << endl;
}


