#include <bits/stdc++.h>
using namespace std;
void printvector(vector<int> v){
    for(auto i : v){
        cout<<i<<" ";
    }
    cout<<endl;
}

int main() {
    string s1 = "hello";
    string s2 = "hf";
    bool a = (s1<s2);
    cout<<a<<endl;
    for(auto i : s1){
        cout<<i<<" ";
    }
    cout<<endl;
    vector<int> v = {1,2,3,4,5,6,7,8,9};
    vector<int> v2 = v;
    for(auto & i : v){
        i*=i;//引用可以改变v的值
    }
    for(auto  i : v2){
        i*=i;
    }
    printvector(v);
    printvector(v2);
    auto l = v2.begin();
    auto r = v2.end();
    auto lv = *(l+1);
    auto rv = *(r-1);
    cout<<lv<<" "<<rv<<endl;

    char aa[10] = "asdfghjkl";
    auto n = begin(aa);
    auto nn = end(aa);
    auto nnn = nn-n;
    typedef int int_array[4];
    typedef int int_array2;
}

