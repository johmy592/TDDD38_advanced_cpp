#include <iostream>
#include <iterator>

using namespace std;

template<typename T>
class Range_Iterator
{
public:
    Range_Iterator(T s, T step = 1) : cur{s}, step_size{step} {}
    
    using iterator_category = std::input_iterator_tag;
    using value_type = T;
    using difference_tpye = long;
    using reference = T;
    using pointer = T const *;
    
    Range_Iterator& operator++()
    {
        cur += step_size;
        return *this;
    }
    Range_Iterator operator++(int)
    {
        Range_Iterator tmp{*this};
        ++*this;
        return tmp;
    }

    reference operator*() const { return cur; }
    bool operator!=(Range_Iterator const & rhs) const
    {
        return (step_size > 0) ? cur < *rhs : cur > *rhs;
    }
    bool operator==(Range_Iterator const & rhs) const
    {
        return !(*this != rhs);
    }
private:
    T cur;
    T step_size;
};

template<typename T>
class Range
{
public:
    using iterator = Range_Iterator<T>;
    Range(T stop) : start_{0}, stop_{stop}, step_{1} {}
    Range(T start, T stop, T step) : start_{start}, stop_{stop}, step_{step} {}

    iterator begin() const { return iterator{start_,step_}; }
    iterator end() const { return iterator{stop_}; }
private:
    T start_,stop_,step_;
};

template <typename T, typename... Extra>  
auto range(T val, Extra... vals) 
{ 
  return Range<T>{val, vals...}; 
}


int main()
{
    { 
        // This block should work when everything is finished
        // print values [0,9[
        for ( int v : range(10) )
            cout << v << ' ';

        // print values 2.3, 2.6, 2.9
        for ( auto v : range(2.3, 3.0, 0.3) )
            cout << v << ' ';

        // prints 2 1 0 -1 (has a negative step size)
        for ( auto v : range(2, -2, -1) )
            cout << v << ' ';
    
        // will not print anything
        for ( auto v : range(2, -1, 3) )
            cout << v << ' ';
    }

    {
        // This block shows some parts of the Range_Iterator class
        Range_Iterator<int> s{2};
        Range_Iterator<int> e{10};
        while ( s != e )
        {
            cout << *s << ' ';
            ++s;
        } // prints 2 3 4 5 6 7 8 9

        //*s = 4; // should not be possible

        Range_Iterator<double> start{2.3, 0.3};
        Range_Iterator<double> stop{3.0};
        while ( start != stop )
        {
            cout << *start++ << ' ';
        } // should print 2.3 2.6 2.9
    }
}
