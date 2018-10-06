/*
 * program6.cc
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define Celestial_Body classes here
class Celestial_Body
{
public:
    virtual ~Celestial_Body() = default;
    Celestial_Body(string name, double size) : name_{name}, size_{size} {}

    string get_name() const { return name_; }
    double get_size() const { return size_;}    

    Celestial_Body& operator=(Celestial_Body const &) = delete;

protected:
    Celestial_Body(Celestial_Body const &) = delete;
private:
    const string name_;
    const double size_;
};

class Star : public Celestial_Body
{
public:
    Star(string name, double size, string galaxy) : Celestial_Body{name,size},
                                                    galaxy_name{galaxy} {}

    string get_galaxy() const { return galaxy_name; }
private:
    string galaxy_name;
};

class Planet : public Celestial_Body
{
public:
    Planet(string name, double size, Celestial_Body& p, double ot, bool pop=false)
        : Celestial_Body{name,size}, parent{p}, orbit_time{ot}, populated_{pop}{}

    Celestial_Body* get_celestial_body() const { return &parent; }
    bool is_populated() const { return populated_; }
    double get_orbit_time() const { return orbit_time; }
    
    void populated(bool p) { populated_ = p; }
    
private:
    Celestial_Body & parent;
    double orbit_time;
    bool populated_;
};

class Moon : public Planet
{
public:
    Moon(string name, double size, Planet& p, double ot, bool pop=false) :
    Planet{name,size,p,ot,pop} {}
};

void print(const Celestial_Body& cb)
{
   // Depending on kind of celestial body, print its correspending data. Output
   // shall be as follows:
   // Helios: star, radius 696342.0 km, belongs to galaxy Milky Way
   // Earth: planet, radius 6371.0 km, belongs to star Helios, orbit time 365.2 days, populated
   // Moon: moon, radius 1737.1 km, belongs to planet Earth, orbit time 27.3 days, not populated
    cout << cb.get_name() << ": ";
    
    auto sp = dynamic_cast<const Star*>(&cb);
    auto pp = dynamic_cast<const Planet*>(&cb);
    auto mp = dynamic_cast<const Moon*>(&cb); 
    if(sp) 
    { 
        cout << "star, "; 
    }else if(pp && !mp)
    {
        cout << "planet, ";
    }else
    {
        cout << "moon, ";
    }
    cout << cb.get_size() << "belongs to ";
    if(sp)
    {
        cout << "galaxy " << sp->get_galaxy() << "\n";
        return;
    }else if(pp && !mp)
    {
        cout << "star " << pp->get_celestial_body()->get_name() << ", ";
    }else
    {
        cout << "planet " << mp->get_celestial_body()->get_name() << ", ";
    }
    cout << "orbit time " << pp->get_orbit_time() << "days, ";
    if(pp->is_populated())
    {
        cout << "populated" << "\n";
    }else
    {
        cout << "not populated" << "\n";
    }
    
}

int main()
{
   // Declare statically one object of each of type Star, Planet, and Moon. Use
   // the following data to initialize the objects (use defaults when suitable):
   // Star: name Helios, radius 696342.0, belongs to galaxy Milky Way
   // Planet: name Earth, radius 6371.0, belongs to star Helios, orbit time 365.2 days, populated
   // Moon: name Moon, radius 1737.1, belongs to planet Earth, orbit time 27.3 days, not populated
    vector<Celestial_Body> bodies;
    Star helios{"Helios",696342.0, "Milky Way"};
    Planet earth{"Earth",6371.0,helios,365.2,true};
    Moon moon{"Moon",1737.1,earth, 27.3};
    
   // Call print() for each object above.
    print(helios);
    print(earth);
    print(moon);
    return 0;
}
