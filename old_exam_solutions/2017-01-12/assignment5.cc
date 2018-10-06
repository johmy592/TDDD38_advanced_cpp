#include <vector>
#include <iostream>
#include <string>
using namespace std;


//The prints are done poorly here...
// NOTE: "..discards qualifiers error" was due to object being const and not the
// functions called.
class Game
{
public:
    virtual ~Game() = default;
    
    string name() const { return name_; }
    virtual bool choose() const 
    {
        int num_players;
        cout << "Number of players: ";
        cin >> num_players;
        if(num_players >= min_players and num_players <= max_players)
        {
            return true;
        }
        return false;
        
    }
    virtual void print(ostream& os) const {};

    Game(Game const &) = delete;
    Game & operator=(Game const &) = delete;

protected:
    Game(string name, int min, int max) : name_{name}, min_players{min}, 
                                          max_players{max} {}
    int min_players;
    int max_players;
    string name_;
    
};

class Board_Game : public Game
{
public:
    Board_Game(string name, int min, int max, int w, int h) : 
                Game{name, min, max}, width {w}, height{h} {}

    string size() const 
    { 
        return to_string(width) + "x " + to_string(height);
    }

    bool choose() const  override
    {
        if(!Game::choose()) { return false; }
        cout << "Board size is: " << size() << " do you have room? ";
        string s;
        cin >> s;
        return s == "yes";
    }
    
    void print(ostream& os) const override
    {
        os << game_type() << name_ << " has " << to_string(min_players) << "-"
           << to_string(max_players) << "and a board size of " << size() << "\n"; 
    }
private:
    int width;
    int height;
    virtual string game_type() const { return "Board game "; }
};

class Cooperative : public Board_Game
{
public:
    Cooperative(string name, int min, int max, int w, int h, bool t=false) :
                Board_Game{name,min,max,w,h}, traitor_present{t} {}
    
    
    bool choose()  const override
    {
        if(!Board_Game::choose()) { return false; }
        cout << "Do you want a traitor? (yes/no): ";
        string s;
        cin >> s;
        return s == "yes";
    }

    void print(ostream& os) const override
    {
        os << game_type() << name_ << "has " << to_string(min_players) << "-" 
           << to_string(max_players) << " and a board size of " << size();
        if(traitor_present) { os << " and has a traitor\n"; }
        else { os << "\n";}
    }
private:
    bool traitor_possible;
    bool traitor_present; 
    string game_type() const override { return "Cooperative board game "; }
};

class Card_Game : public Game
{
public:
    Card_Game(string name, int min, int max, bool s) : 
              Game{name,min,max}, use_standard{s} {}

    void print(ostream& os) const override
    {
        os << game_type() << name_ << "has " << to_string(min_players) << "- "
           << to_string(max_players);
        if(use_standard){ os << " and uses a standard deck of cards\n"; }
        else{ os << " and uses a special deck of cards \n"; }
    }     

private:
    string game_type() const { return "Card game "; }
    bool use_standard;
};

void select_game(vector<Game*> const & games)
{
    for ( Game const * g: games )
    {
        if ( g->choose() )
        {
            g->print(cout);
            cout << endl;
        }
    }
}

int main()
{
    /* Create the following objects dynamically and store them in a vector
     *
     * Board game "Monopoly" has 2-4 players with a board of size 51x51cm
     * Cooperative board game "Pandemic" has 2-5 players with a board size 41x57cm
     * Card game "Solitaire" has 1 player and is played with a normal deck
     * Card game "Bang!" has 3-7 players and is played with a special deck
     * Cooperative board game "Battle Star Galactica" has 4-7 players with a board size of 100x120cm and can have a traitor
     */
    vector<Game*> games{};
    games.emplace_back(new Board_Game{"Monopoly",2,4,51,51});
    games.emplace_back(new Cooperative{"Pandemic",2,5,41,57});
    games.emplace_back(new Card_Game{"Solitaire",1,1,true});
    games.emplace_back(new Card_Game{"Bang!",3,7,false});
    games.emplace_back(new Cooperative{"BSG",4,7,100,120,true});

    select_game(games); 
     // call select_game, below are two examples:
     //
     /* 1:
      * How many players?: 2
      * Do you have space for 51x51cm [y/n]: y
      * -> Board game "Monopoly" has 2-4 players with a board of size 51x51cm
      * How many players?: 1
      * How many players?: 2
      * How many players?: 4
      * -> Card game "Bang!" has 3-7 players and is played with a special deck
      * How many players?: 5
      * Do you have space for 100x120cm? [y/n]: y
      * Do you want a traitor? [y/n]: y
      * -> Cooperative board game "Battle Star Galactica" has 4-7 players with a board size of 100x120cm and can have a traitor

      * 2:
      * How many players?: 2
      * Do you have space for 51x51cm? [y/n]: n
      * How many players?: 3
      * Do you have space for 41x57cm? [y/n]: y
      * Do you want a traitor? [y/n]:
      * -> Cooperative board game "Pandemic" has 2-5 players with a board size 41x57cm
      * How many players?: 5
      * How many players?: 5
      * -> Card game "Bang!" has 3-7 players and is played with a special deck
      * How many players?: 2
      */

}
