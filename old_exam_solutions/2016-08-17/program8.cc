#include <string>
#include <iostream>
#include <sstream>
struct Hexadecimal
{
    
    template<typename T>
    static std::string convert(T const & val) 
    {
        std::ostringstream os;
        os << "0x" << std::hex << val;
        return os.str(); 
    }
};

struct Quoted
{
    
    template<typename T>
    static std::string convert(T const & val) { return "\""+std::to_string(val) + "\""; }
};


template<typename T, typename Conversion>
class Wrapper
{
public:
	Wrapper(const T value) : value_{value} {}
	void set(const T value) { value_ = value; }
	T get() const { return value_;}
	std::string str() const;
private:
	T value_;
};

template<typename T,typename Conversion>
std::string Wrapper<T,Conversion>::str() const 
{ 
    return Conversion::convert(value_);
}


int main()
{
    Wrapper<int,Quoted> w1{1};
    std::cout << w1.str();
    
    Wrapper<double, Hexadecimal> w2{2};
    std::cout << w2.str();

    return 0;
}

