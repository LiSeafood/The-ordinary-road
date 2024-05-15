#ifndef SCORELIST_H
#define SCORELIST_H
#include<iostream>
#include<QString>
using std::string;
class scorelist
{
public:
    string n;
    string name;
    string scores;
    string time;
    scorelist(string a,string b,string c,string d):n(a),name(b),scores(c),time(d){}
    scorelist(){}
};



#endif // SCORELIST_H
