#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void read_lines(string filename, vector<string> &lines)
{
    ifstream input;
    string line;
    input.open(filename);

    if (input.is_open())
    {
        while (getline(input, line))
        {
            lines.push_back(line);
        }
    }
    input.close();
}

int main()
{

}
