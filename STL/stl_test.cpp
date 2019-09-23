//
// Created by sxg on 2019/9/22.
//

#include <iostream> //std::cout
#include <algorithm> // std::for_each
#include <vector>
#include <functional>

using namespace std;

namespace jj35 {
    void myfunc(int i) {
        cout << ' ' << i;
    }

    struct myclass {
        void operator() (int i) {
            cout << ' ' << i;
        }
    } myobj;

    void test_for_each() {
         cout << "test for_each():" << endl;
         vector<int> vec;
         vec.push_back(10);
         vec.push_back(20);
         vec.push_back(30);

         for_each(vec.begin(), vec.end(), myfunc); //output: 10 20 30
         cout << endl;

         for_each(vec.begin(), vec.end(), myclass()); // output: 10 20 30
//         for_each(vec.begin(), vec.end(), myobj);
         cout << endl;

         //since C++ 11 range-based for-statement
         for (auto& elem : vec) {
             elem += 5;
         }

         for (auto elem : vec) {
             cout << ' ' << elem; // output: 15 25 35
         }
    }
}

namespace sxg {
    void test_replace_if() {
        vector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        vec.push_back(40);

        for (auto elem : vec) {
            cout << " " << elem;
        }
        cout << endl;
        replace_if(vec.begin(), vec.end(), bind2nd(less<int>(), 30), 8);



        cout << "after replace:" << endl;
        for (auto elem : vec) {
            cout << " " << elem;
        }
        cout << endl;

        cout << "test replace_copy" << endl;
        vector<int> new_vec(vec);
        replace_copy(vec.begin(), vec.end(), new_vec.begin(), 30, 20);
        for (auto elem : new_vec) {
            cout << " " << elem;
        }
        cout << endl;

        cout << "after replace:" << endl;
        for (auto elem : vec) {
            cout << " " << elem;
        }
        cout << endl;
    }

    void test_lower_bound() {
        vector<int> vec = {10, 10, 20, 20, 20, 30, 30};
        auto lower = lower_bound(vec.begin(), vec.end(), 20);
        cout << typeid(lower).name() << endl;
        cout << *lower << endl;

        auto position = binary_search(vec.begin(), vec.end(), 30);
        cout << boolalpha << position << endl;
    }
}

namespace sxg01 {
    double my_divide(double x, double y) {
        return x/ y;
    }

    struct Mypair {
        double a, b;
        // memeber function 有个argument：this
        double multipy() {
            return a * b;
        }
    };
    void test_bind() {
        using namespace std::placeholders; // add visibility of _1, _2, _3

        // binding functions
        auto fn_five = bind(my_divide, 10, 2);
        cout << fn_five() << endl;

        auto fn_half = bind(my_divide, _1, 2);
        cout << fn_half(10) << endl;

        auto fv_invert = bind(my_divide, _2, _1);
        cout << fv_invert(10, 2) << endl; // 0.2

        auto fn_rounding = bind<int>(my_divide, _1, _2);
        cout << fn_rounding(10, 3) << endl;

        // binding memebers
        Mypair ten_two {10, 2};

        auto bound_memfn = bind(&Mypair::multipy, _1);
        cout << bound_memfn(ten_two) << endl;

        auto bound_memdata = bind(&Mypair::a, ten_two); //return ten_two.a
        cout << bound_memdata() << endl; // 10

        auto bound_memdata2 = bind(&Mypair::b, _1);
        cout << bound_memdata2(ten_two) << endl;


        vector<int> v{15, 37, 94, 50, 73, 58, 28, 98};
        int n = count_if(v.cbegin(), v.cend(), not1(bind2nd(less<int>(), 50)));
        cout << "n = " << n << endl; // 5

        auto fn = bind(less<int>(), _1, 50);
        cout << count_if(v.cbegin(), v.cend(), fn) << endl; // 3

    }
}

#include <list>
#include <iterator>

namespace sxg02 {


    void test_inserter() {
        list<int> foo, bar;
        for (int i = 0; i < 5; ++i) {
            foo.push_back(i);
            bar.push_back(i*10);
        }

        list<int>::iterator it = foo.begin();
        advance(it, 3);
        copy(bar.begin(), bar.end(), inserter(foo, it));

        for (const auto& x : foo) {
            cout << x << " ";
        }
        cout << endl;
    }
}

namespace sxg03 {
    void test_ostream_iterator() {
        vector<int> vec;
        for (int i = 0; i < 10; i++) {
            vec.push_back(i*10);
        }

        std::ostream_iterator<int> out_it(std::cout, ", ");
        std::copy(vec.begin(), vec.end(), out_it);
    }

    void test_istream_iterator() {
        double value1, value2;
        std::cout << "Please input two values:";
        std::istream_iterator<double>eos; // end-of-stream iterator
        std::istream_iterator<double> iit(std::cin); //stdin iterator

        if (iit != eos) {
            value1 = *iit;
        }

        ++iit;

        if (iit != eos) value2 = *iit;

        std::cout << value1 << "*" << value2 << "=" << (value1*value2) << endl;

        vector<int> c {10, 20, 30};
        copy(iit, eos, inserter(c, c.begin()));
        for (auto x : c) {
            cout << x << " ";
        }
        cout << endl;
    }


}

int main() {
//    jj35::test_for_each();
//    sxg::test_replace_if();
//    sxg::test_lower_bound();
//    sxg01::test_bind();
//    sxg02::test_inserter();
    sxg03::test_ostream_iterator();
    sxg03::test_istream_iterator();
    return 0;
}
