#include <sstream>
#include <iterator>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
using namespace std;



// Given, should not be changed
struct Image_Data
{
    Image_Data(string const & line)
    {
        istringstream iss{line};
        iss >> type;
        for ( int d; iss >> d; )
        {
            args.push_back(d);
        }
    }
    string type;
    vector<int> args;
};

// Add your classes here
class Image
{
public:
    virtual ~Image() = default;

    virtual int size() const = 0;

protected:
    Image(int width, int height) : width_{width}, height_{height} {}
    int width_;
    int height_;
};

class PNG : public Image
{
public:
    //static because function belongs to class, not 1 specific object
    static PNG* parse(Image_Data const & data) 
    {
        if(data.type == "PNG")
        {
            return new PNG{data.args[0], data.args[1]};
        }else{
            return nullptr;
        }
    }
    
    int size() const override { return 1.5*width_*height_; }
private:
    PNG(int width, int height) : Image{width, height} {}
};

class BMP : public Image
{
public:
    BMP(int width, int height) : Image{width, height} {}
    static BMP* parse(Image_Data const & data)  
    {
        if(data.type == "BMP")
        {
            return new BMP{data.args[0], data.args[1]};
        }else{
            return nullptr;
        }
    }

    int size() const override { return 3*width_*height_; }
};


class JPG : public Image
{
public:
    JPG(int width, int height, int quality) : Image{width, height},
                                              quality_{quality} {}

    static JPG* parse(Image_Data const & data) 
    {
        if(data.type == "JPG")
        {
            return new JPG{data.args[0], data.args[1], data.args[2]};
        }else{
            return nullptr;
        }
    }

    int size() const override { return 3*width_*height_*(quality_/100.0); }
private:
    int quality_;
};




/*
 * Given code. No modifications allowed unless specified!
 */
Image* error_printer(Image_Data const & d)
{
    cout << "!!! " << d.type << " is an invalid file format !!!\n";
    return nullptr;
}
int main()
{
    vector<unique_ptr<Image>> images;
    vector<function<Image*(Image_Data const &)>> funs { PNG::parse,
                                                        JPG::parse,
                                                        BMP::parse,
                                                        error_printer};
    cout << "Enter one line for each image on the format \"type [type specific data]\". Exit with \"q\".\n\n";

    for ( string line; getline(cin, line); )
    {
        if ( line == "q" )
        {
            break;
        }
        Image_Data data{line};
        for ( auto && f: funs )
        {
            if (auto ptr = f(data))
            {
                images.emplace_back(ptr);
                break;
            }
        }
    }

// Additions allowed below (calculate and print sum)
    int bytes = {};
    for(auto && i : images)
    {
        bytes += i->size();
    }
    cout << "Total size: " << bytes;



}
