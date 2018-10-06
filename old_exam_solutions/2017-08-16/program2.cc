#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;
class Slab
{
public: 
    virtual ~Slab() = default;

    string get_size() const { return size; }
    double get_weight() const { return weight; }
    string get_color() const { return color; }
    virtual Slab* clone() const = 0;
protected:
    Slab() = default;
    Slab(string color_, string size_, double weight_) : color{move(color_)}, size{move(size_)}, weight{weight_}{}
    Slab(Slab const &) = default;
    

private:
    string color;
    double weight;
    string size;
};

class Concrete : public Slab
{
public:
    Concrete() = default;
    Concrete(string color_, string size_, double weight_, bool tumbled_ = false) : Slab{move(color_), move(size_), weight_}, is_tumbled{tumbled_} {}    

    bool tumbled() const { return is_tumbled; }
    Concrete* clone() const override
    {
        return new Concrete{*this};
    }
private:
    bool is_tumbled;
};

class Rock : public Slab
{
public:
    Rock() = default;
    Rock(string size_, double weight_, string type_) : Slab{"Nature",size_, weight_}, type{type_} {}

    string get_type() const  { return type; }
    Rock* clone() const override
    {
        return new Rock{*this};
    }
private:
    string type;
};

class Brick : public Slab
{
public:
    Brick(string color_, string size_, double weight_) : Slab{color_,size_,weight_}{}
    
    Brick* clone() const override
    {
        return new Brick{*this};
    }
};

void test(Slab const & s)
{
     // Create a copy of the object that s refers to
    //
    // Print the information about the copy. With objects constructed according to the
    // comments in main, the printout should be:
    // Concrete: Gray, 25x12x4, 2.8kg
    // Rock: Granite, Nature, 12x15x10, 10.5kg
    // Brick: Red, 25x10x10, 3.2kg
    // Concrete: Graphite, 20x20x6, 3.9kg, tumbled
    //
    // Destroy the copy
    Slab const * p = s.clone();
    if ( dynamic_cast<Concrete const*>(p) )
    {
        cout << "Concrete: ";
    }
    else if (auto r = dynamic_cast<Rock const*>(p) )
    {
        cout << "Rock " << r->get_type() << ": ";
    }
    else
    {
        cout << "Brick: ";
    }
    cout << p->get_color() << ", " << p->get_size() << ", " << p->get_weight() << "kg";
    auto c = dynamic_cast<Concrete const *>(p);
    c;
    if ( auto c2 = dynamic_cast<Concrete const *>(p) && c->tumbled())
    {
        cout << ", tumbled";
    }
    cout << endl;
    delete p;
   
}

int main()
{
    // Create the following objects dynamically and store in some kind of container:
    // Type      Color    Size      Weight   type/tumbled
    // --------------------------------------------------
    // Concrete  Gray     25x12x4   2.8
    // Rock               12x15x10  10.5     Granite
    // Brick     Red      25x10x10  3.2
    // Concrete  Graphite 20x20x6   3.9      true

    // pass each object to test.
   
    vector<unique_ptr<Slab>> slabs;
    slabs.emplace_back(make_unique<Concrete>("Gray","25x12x4",2.8));
    slabs.emplace_back(make_unique<Rock>("12x15x10",10.5, "Granite"));
    slabs.emplace_back(make_unique<Brick>("Red", "25x25x10",3.2));
    slabs.emplace_back(make_unique<Concrete>("Graphite","20x20x6",3.9, true));
 
    for(auto && s : slabs)
    {
        test(*s);
    }

    
    
   return 0;
}
