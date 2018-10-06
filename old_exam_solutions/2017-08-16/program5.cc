#include <iostream>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
    //1
    vector<int> vals{istream_iterator<int>{cin}, istream_iterator<int>{} };
    
    //2
    cout << vals.size() << " values read \n";
    copy(begin(vals), end(vals), ostream_iterator<int>{cout, " "});
    cout << '\n';

    //3
    sort(begin(vals), end(vals), greater<int>{});    
     
    //4 
    vals.erase(unique(begin(vals),end(vals)), end(vals));
    
    //5
    cout << "Unique values in decennding order: " << '\n';
    copy(begin(vals), end(vals), ostream_iterator<int>{cout, " "});
   
    //6
    int num = floor(vals.size()*0.05);
    cout << '\n' << "Num: " << num << endl;

    //7
    cout << "Smallest and largest values removed: " << '\n';
    vals.erase(begin(vals), begin(vals)+num);
    vals.erase(end(vals) - num, end(vals)); 
    copy(begin(vals), end(vals), ostream_iterator<int>{cout, " "});

    //8
    auto mean_val = accumulate(begin(vals), end(vals),0.0)/vals.size();
    cout << "Mean value: \n" << mean_val;

    //9
    auto diff_sum = accumulate(begin(vals), end(vals), 0.0, [mean_val](double s, auto v){ return s + abs(mean_val - v); });
    
    cout << "Sum of differences: \n" << diff_sum;



    return 0;
}
