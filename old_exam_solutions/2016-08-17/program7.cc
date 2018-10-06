#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
    vector<double> values{istream_iterator<double>{cin}, istream_iterator<double>{}};

    auto num_vals = values.size();
    double sum_vals = accumulate(begin(values),end(values),0);
    double mean = sum_vals/num_vals;
    auto minmax_val = minmax_element(begin(values), end(values));

    size_t mid = num_vals/2;
    nth_element(begin(values),begin(values)+mid,end(values));
    double med = static_cast<double>(values.at(mid));
    if(num_vals%2 == 0)
    {
        nth_element(begin(values),begin(values)+mid-1,end(values));
        med = (med + values.at(mid-1))/2;
    }
 
    double diffs{};
    for_each(begin(values),end(values),
                [&diffs,mean](double& a) {diffs += pow((mean-a),2);});
    //double stddev = sqrt(accumulate(begin(values),end(values),0.0)/num_vals);
    double stddev{sqrt(diffs/num_vals)}; 
    cout << "min value.........: " << *minmax_val.first << "\n";
    cout << "max value.........: " << *minmax_val.second << "\n";
    cout << "mean..............: " << mean << "\n";
    cout << "median............: " << med << "\n";
    cout << "standard deviation: " << stddev;
    return 0;
}
