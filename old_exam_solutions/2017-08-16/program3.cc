#include <vector>
#include <algorithm>
#include <forward_list>
#include <iostream>

using namespace std;
template<typename it, typename Comparison = std::less<typename it::value_type>>
void ssort(it start, it end, Comparison comp = {})
{
    for ( it cur{start}; cur != end; ++cur )
    {
        auto cur_min = min_element(cur, end, comp);
        iter_swap(cur,cur_min);
    }
}

int main()
{
    forward_list <string> lst {"hello","this","is","a","test"};
    vector<int> lst2{5,2,4,7,9,2};
    ssort(begin(lst), end(lst), [](string a, string b){ return a.length() < b.length(); });
    ssort(begin(lst2), end(lst2));
    for(auto i : lst)
    {
        cout << i;
    }
    for(auto i : lst2)
    {
        cout << i << endl;
    }

    return 0;
}
