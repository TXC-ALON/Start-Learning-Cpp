#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main(){
        unsigned int a = -1;
        unsigned char b = -1;
        int c = b;
        cout<<a<<endl;
        cout<<b<<endl;
        cout<<"hello"<<endl;
        cout<<c<<endl;
        /*   output
        65535
        
        hello
        255
        */
        cout<<endl;
        unsigned u = 10,u2 = 42;
        int i = 10,i2 = 42;
        cout<<u2-u<<endl;
        cout<<u-u2<<endl;
        cout<<i2-i<<endl;
        cout<<i-i2<<endl;
        cout<<i-u<<endl;
        cout<<u-i<<endl;
        cout<<'\a'<<endl;
        int mm(4);
        cout<<mm<<endl;
        string m("abcdefg");
        cout<<m<<endl;
        cout<<endl;

        int val = 42;
        int *p = &val;
        int r = *p;
        cout<<r<<endl;
        cout<<p<<endl;
        cout<<*p<<endl;
        cout<<*p+1<<endl;
        cout<<*(p+1)<<endl;
        cout<<*(p+2)<<endl;

        cout<<endl;
        int k = 42;
        int *pp;
        int *&rr = pp;
        rr = &k;
        *rr = 0;
        cout<<k<<endl;
        cout<<endl;

        int tt = 9;
        int *ttp = &tt;
        const int *ttp2 = ttp;
        *ttp = 5;
        cout<<*ttp2<<endl;
        cout<<endl;

        const int ci = 0, &cj = ci;
        // x的类型是const int
        decltype(ci) ww = 0;
        // y的类型是const int &
        decltype(cj) yy = ww;


}