#include <sstream>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

//This assignment did not work out LUL
int main()
{
    //1
    vector<string> words{istream_iterator<string>{cin},
                         istream_iterator<string>{}};
    
    //2
    vector<pair<string,int>> freq;
    for_each(begin(words),end(words),
            [&freq,words](string w){ 
                freq.emplace_back(make_pair(w,count(begin(words),end(words),w)));
            });
    
    //3
    sort(begin(freq), end(freq), 
        [](pair<string,int> p1, pair<string,int>p2)
        {
            return get<1>(p1) > get<1>(p2);
        });

    
    //4
    vector<string> replace(10);
    transform(begin(freq), next(begin(freq),10), begin(replace), 
            [](auto p) { return get<0>(p); });
    
    //5
    transform(begin(words), end(words), begin(words),
            [&replace](string w){
                auto it = find(begin(replace),end(replace),w);
                if(it != end(replace)) { 
                    return "$"+ to_string(distance(begin(replace), it));
                }else{
                    return w;
                }
            });

    //8
   transform(begin(replace), end(replace), ostream_iterator<string>{cout, ";"},
              [index=0](string s) mutable { 
                ostringstream oss;
                oss << '$' << index++ << '=' << s;
                return oss.str();
                });
    cout << "\n";
 
    //7
    copy(begin(words), end(words), ostream_iterator<string>{cout, " "});

    return 0;
}
