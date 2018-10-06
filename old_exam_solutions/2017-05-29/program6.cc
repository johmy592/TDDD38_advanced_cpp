#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Fruit
{
public:
    virtual ~Fruit() = default;
    
    virtual string name() const = 0;
    virtual int vitamin_c_content() const = 0;
    virtual bool dehiscent() const = 0;
    
    int mass() const { return mass_; }
protected:
    Fruit() = default;
    Fruit(double mass) : mass_{mass} {}

    // Better to make another function concentration() and keep
    // mass_ private.
    double mass_;
};

class Berry : public Fruit
{
public:
    virtual ~Berry() = default;
    bool dehiscent() const override final { return false; }
protected:
    Berry() = default;
    Berry(double mass) : Fruit{mass} {}
};

class Lemon : public Berry
{
public:
    Lemon() = default;
    Lemon(double mass) : Berry{mass} {}
    
    string name() const override { return "Lemon"; }
    int vitamin_c_content() const override { return mass_*5.3; }
    
}; 

class Apple : public Fruit
{
public:
    Apple() = default;
    Apple(double mass) : Fruit{mass} {}

    string name() const override { return "Apple"; }
    int vitamin_c_content() const override { return mass_*0.46; }
    bool dehiscent() const override { return false; }
    
};

class Pea : public Fruit
{
public:
    Pea() = default;
    Pea(double mass) : Fruit{mass} {}

    string name() const override { return "Pea"; }
    int vitamin_c_content() const override { return mass_*4; }
    bool dehiscent() const override { return true; }
};

void print(Fruit const & f)
{
    // Print Berry if f is a berry or Fruit otherwise
    if(dynamic_cast<Berry const *>(&f)) { cout << "Berry, "; }
    else { cout << "Fruit, "; }
    cout << f.name() << " with mass " << f.mass() << "g [";
    if ( !f.dehiscent() )
    {
        cout << "in";
    }
    cout << "dehiscant]\n";

}

int main()
{
    // create a vector containing the following fruits:
    //  Apple, mass: 150g
    //  Lemon, mass: 75g
    //  Pea, mass: 25g
    //
    vector<Fruit*> fruits;
    fruits.emplace_back(new Apple(150));
    fruits.emplace_back(new Lemon(75));
    fruits.emplace_back(new Pea(25));
    // Iterate through the vector and pass each fruit to print above, should give the following output
    // Fruit, Apple with mass 150g [indehiscant]
    // Berry, Lemon with mass 75g [indehiscant]
    // Fruit, Pea with mass 25g [dehiscant]

    // (auto && ) ?
    for(auto f : fruits)
    {
        print(*f);
    }
   int total_content {};
    // Calculate the total vitamin C content of all fruit
    for(auto f :fruits)
    {
        total_content += f->vitamin_c_content();
    }
    cout << "Total vitamin C content: " << total_content << endl;
}
