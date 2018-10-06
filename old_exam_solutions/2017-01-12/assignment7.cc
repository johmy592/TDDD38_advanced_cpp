#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

using namespace std;


class Student
{
public:
    Student() = default;
    Student(string sname, string fname, string pnumber, char g, int p) :
            surname{sname}, first_name{fname}, pnr{pnumber}, grade{g}, points{p} 
    {
        if(grade == 'U') { gn = 0; }
        else if(grade == '5') { gn = 5; }
        else if(grade == '4') { gn = 4; }
        else if(grade == '3') { gn = 3; }
        else{ gn = 0; }
     }
    
    string to_str() const
    {
        return surname + ", " + first_name + "   "  + grade 
               + "(" + to_string(points) + ")" + '\n';
    }

    bool operator<(Student const & rhs) const
    {
        if(gn < rhs.gn) 
        { 
            return false; 
        }
        else if( gn > rhs.gn)
        {
            return true;
        }
        else
        {
            return (surname + first_name) < (rhs.surname + rhs.first_name);
        } 
    }

private:
    string surname;
    string first_name;
    string pnr;
    char grade;
    int points;
    int gn;
};

istream& operator>>(istream & st, Student & s)
{
    string firstname;
    string surname;
    string pnr;
    char grade;
    int points;

    getline(st,firstname, ':');
    getline(st,surname,':');
    getline(st,pnr,':');
    st >> points;
    st.ignore();
    st.get(grade);
    st.ignore(); 
    
    s = Student(surname,firstname,pnr,grade,points);
    return st;
}

int main()
{
    vector<Student> students{istream_iterator<Student>{cin},
                            istream_iterator<Student>{}};
        
    
    sort(begin(students), end(students));


    for_each(begin(students),end(students), 
            [](Student const & s) { cout << s.to_str(); });
    return 0;
}
