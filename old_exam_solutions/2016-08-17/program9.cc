#include <vector>
#include <iostream>
using namespace std;

template<typename T, class Container = vector<T>>
class Cycler
{
public:
    Cycler(Container & cont) : c{cont}, cur{begin(cont)} {}
        
    T& next() 
    {
        T& prev{*cur};
        cur++;
        if(cur == end(c))
        {
            cur = begin(c);
        }
        return prev;
    }

    void reset() 
    {
        cur = begin(c);
    }
    
    size_t size() const { return c.size(); }

private:
    Container & c;    
    decltype(begin(c)) cur; //or Container::iterator
    
};

int main()
{
    vector<int> v{1,2,3};
    Cycler<int> c{v};
    cout << c.next() << c.next() << c.next() << c.next();
    c.reset();
    
    cout << "Size: " << c.size() << ", ";
    return 0;
}
