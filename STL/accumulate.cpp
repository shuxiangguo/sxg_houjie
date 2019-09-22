//
// Created by sxg on 2019/9/22.
//

// 侯捷老师的STL中的accumulate算法
#include <iostream> //std::out
#include <functional> //std::minus
#include <numeric> //std::accumulate
using namespace std;

namespace jj34 {
    int myfunc(int x, int y) {
        return x + 2*y;
    }

    struct myclass {
        int operator() (int x, int y) {
            return x + 3*y;
        }
    };

    void test_accumulate() {
        cout << "test accumulate()..........." << endl;
        int init = 100;
        int nums[] = {10, 20, 30};

        cout << "using default accumulate:";
        cout << accumulate(nums, nums + 3, init);//160
        cout << endl;

        cout << "using functional's minus:";
        cout << accumulate(nums, nums+3, init, minus<int>()); //40
        cout << endl;

        cout << "using custom function:";
        cout << accumulate(nums, nums+3, init, myfunc); //220
        cout << endl;

        cout << "using custom object:";
        cout << accumulate(nums, nums+3, init, myclass()); //280
        cout << endl;
    }
}



int main() {
    jj34::test_accumulate();
    return 0;
}