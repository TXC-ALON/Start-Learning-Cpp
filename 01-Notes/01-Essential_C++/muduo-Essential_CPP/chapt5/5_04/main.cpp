#include "fibonacci.hpp"
#include <typeinfo>

int main()
{
    Fibonacci fib;
    Fibonacci fib2;
    num_sequence ns;

    num_sequence * pns = &fib;

	int iVal;
    double dVal;

	cout << typeid(iVal).name() << endl;
	cout << typeid(dVal).name() << endl;
    

    cout << fib.what_am_i() << endl;
    cout << pns->what_am_i() << endl;
    cout << typeid(fib).name() << endl;
    cout << typeid(fib2).name() << endl;
    cout << (typeid(fib)==typeid(Fibonacci)) << endl;
    cout << (typeid(fib)==typeid(fib2)) << endl;

    cout << typeid(ns).name() << endl;
    cout << (typeid(fib)==typeid(ns)) << endl;

    cout << typeid(*pns).name() << endl; 

    return 0;
}

// -Wall == warning all