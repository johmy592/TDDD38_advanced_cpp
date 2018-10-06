#include <vector>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
    //1
    vector<string> words{istream_iterator<string>{cin}, 
                          istream_iterator<string>{}};
    

    //2
    cout << "Total number of words read: " << words.size() << '\n';

    //3
    for_each(begin(words), end(words),
             [](string & s) { 
                transform(begin(s), end(s), begin(s),::tolower); });

    //4
    sort(begin(words), end(words));
    //5
    words.erase(unique(begin(words), end(words)), end(words));
    //6
    cout << "Total number of unique words: " << words.size() << '\n'; 
    //7
    cout << '\n' << "The unique words in alphabetical order: \n";
    copy(begin(words), end(words), ostream_iterator<string>(cout," "));
    //8
    stable_sort(begin(words), end(words), 
        [](string const & w1, string const & w2) 
        { 
            if(w1.length() < w2.length())
            { 
                return true; 
            }else 
            { 
                return w1 < w2; 
            }
        });
    //9
    cout << "\n\n The unique words ordered by length:\n ";
    copy(begin(words), end(words), ostream_iterator<string>{cout, " "});
    return 0;
}
