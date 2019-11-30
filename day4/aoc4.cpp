#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <iterator>

using namespace std;

void read_and_sort(string filename, vector<string> &lines)
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
    sort(lines.begin(), lines.end());
    input.close();
}

void write_file(string filename, map<int, vector<int> > &content)
{
    ofstream output;
    output.open(filename);
    for(auto const &value: content)
    {
        output << "GUARD " << value.first << " sleep minutes:" << endl;
        for (const int &mins: value.second)
        {
            output << mins << endl;
        }
    }
    output.close();
}

typedef enum GUARD_STATE
{
    SHIFT,
    ASLEEP,
    AWAKE,
}GUARD_STATE;

void find_sleep_minutes(int atime, int stime, vector<int> &vec)
{
    while (atime > stime)
    {
        vec.push_back(stime);
        stime++;
    }
}

string print_vec(const vector<int> &vec, const string delimiter) {
    stringstream  s;
    copy(vec.begin(),vec.end(), ostream_iterator<int>(s,delimiter.c_str()));
    return s.str();
}

int find_minute_sleepiest(map<int, vector<int> > &db)
{
    int mins_slept = 0;
    int result = 0;
    int sleepiest_guard;
    for (auto const &pair: db)
    {
        if (pair.second.size() > mins_slept)
        {
            sleepiest_guard = pair.first;
            mins_slept = pair.second.size();
        }
    }
    sort(db[sleepiest_guard].begin(), db[sleepiest_guard].end());
    int occurance = 0, last_num = db[sleepiest_guard][0];
    int max_occurance = 0, sleepiest_min = 0;
    for (const int &val: db[sleepiest_guard])
    {
        if (val == last_num)
        {
            occurance++;
            if (occurance > max_occurance)
            {
                max_occurance = occurance;
                sleepiest_min = val;
            }
        }
        else
        {
            last_num = val;
            occurance = 1;
        }
    }
    cout << sleepiest_guard << ": " << sleepiest_min << endl;
    result = sleepiest_min * sleepiest_guard;
    return result;
}

int sleepiest_on_same(map<int, vector<int> > &db)
{
    int max_occurance = 0, occurance = 0, sleepiest_min = 0;
    int last_num, guard_no;
    for (auto &pair: db)
    {
        last_num = pair.second[0];
        sort(pair.second.begin(), pair.second.end());
        for (int val: pair.second)
        {
            if (val == last_num)
            {
                occurance++;
                if (occurance > max_occurance)
                {
                    max_occurance = occurance;
                    sleepiest_min = val;
                    guard_no = pair.first;
                }
            }
            else
            {
                last_num = val;
                occurance = 1;
            }
        }
    }
    cout << guard_no << ": " << sleepiest_min << endl;
    return guard_no * sleepiest_min;
}

void parse_lines(vector<string> &lines, map<int, vector<int> > &db)
{
    int guard_id;
    GUARD_STATE state;
    int atime, stime;
    for (const string& line: lines)
    {
        size_t idp = line.find("#");
        size_t ide = line.find(idp, ' ');
        if (idp != string::npos)
        {
            guard_id = stoi(line.substr(idp + 1, ide - idp));
            state = SHIFT;
        }
        else if (line.find("falls asleep") != string::npos)
        {
            if (state == SHIFT || state == AWAKE)
            {
                stime = stoi(line.substr(15, 2));
                state = ASLEEP;
            }
        }
        else if (line.find("wakes up") != string::npos)
        {
            if (state == ASLEEP)
            {
                atime = stoi(line.substr(15, 2));
                find_sleep_minutes(atime, stime, db[guard_id]);
                state = AWAKE;
            }
        }
    }
}

int main() 
{
    vector<string> lines;
    map<int, vector<int> > gdb;
    read_and_sort("input4.txt", lines);
    parse_lines(lines, gdb);
    //cout << find_minute_sleepiest(gdb) << endl;
    cout << sleepiest_on_same(gdb) << endl;
    //write_file("input4_minutes.txt", gdb);
    return 0;
}
