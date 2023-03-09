#include <iostream>
#include <string>
using namespace std;
class Person
{
private:
    string strName;
    string strAddress;

public:
    Person() = default;
    Person(const string &_strName, const string &_strAddress) : strName(_strName), strAddress(_strAddress) {}
    istream &operator>>(istream &is, Person &p)
    {
        is >> p.strName >> p.strAddress;
        return is;
    }
    Person(std::istream &is) { is >> *this; }
    string getName() const { return strName; }
    string getAddress() const { return strAddress; }
    void PersonPrint() { cout << "Personname: " << strName << "\nPersonaddress: " << strAddress << endl; }
};