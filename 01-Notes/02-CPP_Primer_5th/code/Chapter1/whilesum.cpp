#include <iostream>
using namespace std;
int main() {
    int num = 0;int sum = 0;
    std::cout << "Hello, World!" << std::endl;
    while(cin>>num){
        sum += num;
        if(num == 0){
            break;
        }
    }
    cout<<sum<<endl;
    return 0;
}