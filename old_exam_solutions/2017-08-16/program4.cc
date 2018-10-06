#include <vector>
#include <iostream>
#include <iomanip>

// Main function. The output should be
// true
// false
// false
// true

struct All
{
    bool start_value{true};
    bool end_value{false};
    
    template<typename T>
    bool prefix(T const & element)
    {
        return static_cast<bool>(element);
    }

    bool combine(bool v1, bool v2) { return v1 && v2; }
    bool done(bool value) { return !value; }
};

struct Any
{
    static constexpr bool start_value{false};
    static constexpr bool end_value{true};

    template<typename T>
    bool prefix(T const & element)
    {
        return static_cast<bool>(element);
    }

    bool combine(bool v1, bool v2) { return v1 || v2; }
    bool done(bool value) { return value; }
};

struct AtLeast
{
    AtLeast(int N) : count{N} {};
    int count;
    static constexpr bool start_value{false};
    static constexpr bool end_value{true};

    template<typename T>
    bool prefix(T const & element)
    {
        bool val = static_cast<bool>(element);
        if(val){ --count; }
        return false;        
    }

    bool combine(bool , bool){ return false; }
    bool done(bool) { return count == 0; }
};

template<typename it, typename conv_type = All>
bool logic_combine(it start, it end, conv_type policy = {})
{
    bool result = policy.start_value;
    for(it i{start}; i != end; ++i)
    {
        bool val = policy.prefix(*i);
        result = policy.combine(val,result);
        if(policy.done(result)){ return policy.end_value;}
    }
    return result;
} 

int main()
{
    std::vector<int> vals {0,0,0,1};
    auto b { begin(vals) };
    auto e { end(vals) };
    using namespace std;
    cout << boolalpha
         << logic_combine(b,e, AtLeast{1}) << '\n'
         << logic_combine(b,e, AtLeast{8}) << '\n'
         << logic_combine(b,e, Any{}) << '\n'
         << logic_combine(b,e) << '\n';
    /*cout << boolalpha 
        << logic_combine(b,e,All{}) << '\n'
        << logic_combine(b,e,Any{}) << '\n'
        << logic_combine(b,e,AtLeast{3}) << '\n'
        << logic_combine(b,e);*/

}
