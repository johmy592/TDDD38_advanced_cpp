/*
 * program8.cc
 */
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Add and modify stuff according to given specifications. 
template<typename arg, typename ret>
struct Round_Down
{
public: 
    static ret round(arg val) { return floor(val); } 
};

template<typename arg, typename ret>
struct Round_Up
{
public:
    static ret round(arg val) { return ceil(val); }
};

template<typename arg, typename ret>
struct Round_Towards_Zero
{
public:
    static ret round(arg val) { return val > 0 ? ceil(val) : floor(val); }
};

template<typename Val, typename Set,
        // THIS IS HOW A TEMPLATE TEMPLATE ARGUMENT WORKS BRUH: 
        template<typename, typename>class Round_Policy = Round_Towards_Zero>
class Number
{
public:
    Number(Set value = 0.0) : value_(value) {}

    Val  get_value() const { return value_; }
    void set_value(Set value) { value_ = round(value); }

private:
    Val round(Set val) { return Round_Policy<Set, Val>::round(val); }
    Val value_;
};

void test_rounding(double value)
{
    // One object for each of the three rounding policies:
    static Number<int,double,Round_Down> n1;
    static Number<int, float, Round_Up> n2;
    static Number<int, long, Round_Towards_Zero> n3;

    n1.set_value(value);
    n2.set_value(value);
    n3.set_value(value);

    cout << setw(11) << left << value 
         << setw(11) << n1.get_value()
         << setw(11) << n2.get_value() 
         << setw(11) << n3.get_value()
         << '\n';
}

int main()
{
    cout << fixed << setprecision(2) << showpos;
    cout << setw(11) << left << "Value" 
         << setw(11) << "Down" 
         << setw(11) << "Up" 
         << setw(11) << "Towards 0"
         << "\n\n";

    test_rounding(9.67);
    test_rounding(9.5);
    test_rounding(9.35);
    test_rounding(9.0);
    test_rounding(0.0);
    test_rounding(-9.0);
    test_rounding(-9.25);
    test_rounding(-9.5);
    test_rounding(-9.67);

    return 0;
}
