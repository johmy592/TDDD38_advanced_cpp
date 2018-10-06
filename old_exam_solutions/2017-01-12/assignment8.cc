#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iterator>

using namespace std;

int main(int argc, char * argv[])
{
    //1
    if(argc != 3)
    {
        cerr << "Must be called with files containing start and end times\n";
        return 1;
    }
    ifstream start{argv[1]};
    ifstream endstream{argv[2]};
    if(!start || !endstream) 
    {
        cerr << "Invalid filenames \n";
        return 1;
    }
    //2
    // 
    vector<string> intervals;
    transform(istream_iterator<int>{start}, istream_iterator<int>{},
              istream_iterator<int>{endstream}, back_inserter(intervals),
              [](int s, int e)
              {
                if(s > e) { e += 2400; }
                auto minutes = [](int t){return 60 * (t / 100) + t % 100;};
                int et{minutes(e)};
                int st{minutes(s)};
                int tot{et - st};
                int res{100 * (tot / 60) + tot % 60};
                return to_string(res);

              });
       
    cout << "Max interval: " << *max_element(begin(intervals),end(intervals)) <<"\n";
    copy(begin(intervals), end(intervals), ostream_iterator<string>{cout,"\n"}); 
}
