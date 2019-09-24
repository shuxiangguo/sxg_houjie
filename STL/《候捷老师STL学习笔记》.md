# 《候捷老师STL学习笔记》

> 使用一个东西却不明白它的道理，不高明-----侯捷老师

## 1.各种容器的iterators的iterator_category

```c++
// 五种iterator_category
struct input_iterator_tag {}
struct output_iterator_tag {}
struct forward_iterator_tag : public input_iterator_tag {}
struct bidirectional_iterator_tag : public forward_iterator_tag {}
struct random_access_iterator_tag : public bidirectional_iterator_tag {}

```

<img src="/home/sxg/Workspace/cpp/houjie/STL/itertor_category.png" alt="1569082203483"  />



## 2.各种容器的iterators的iterator_category的typeid

示例程序：

```c++
#include<typeinfo> //typeid()
template<typename I>
void display_category(I itr) {
    typename iterator_traits<I>::iterator_category cagy;
    _display_category(cagy);
    cout << "typeid(itr).name() = " << typeid(itr).name() << endl;
}
```

**对于1,2的测试程序如下：**

```c++
//
// Created by sxg on 2019/9/21.
//
#include <typeinfo>
#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
using namespace std;

void _display_category(input_iterator_tag) {
    cout << "input_iterator_tag" << endl;
}

void _display_category(forward_iterator_tag) {
    cout << "forward_iterator_tag" << endl;
}

void _display_category(bidirectional_iterator_tag) {
    cout << "bidirectional_iterator" << endl;
}

void _display_category(random_access_iterator_tag) {
    cout << "random_access_iterator" << endl;
}


void _display_category(output_iterator_tag) {
    cout << "output_iterator" << endl;
}

template<typename I>
void display_category(I itr) {
    typename iterator_traits<I>::iterator_category cagy;
    _display_category(cagy);
    cout << "typeid(itr).name() = " << typeid(itr).name() << endl;
}

int main() {

    display_category(array<int, 5>::iterator());
    display_category(vector<int>::iterator());
    display_category(list<int>::iterator());
    display_category(forward_list<int>::iterator());
    display_category(deque<int>::iterator());

    display_category(set<int>::iterator());
    display_category(map<int, int>::iterator());
    display_category(multiset<int>::iterator());
    display_category(multimap<int,int>::iterator());
    display_category(unordered_set<int>::iterator());
    display_category(unordered_map<int,int>::iterator());

    display_category(istream_iterator<int>());
    display_category(ostream_iterator<int>(cout, ""));

    return 0;
}


```

**输出结果**:

<img src="/home/sxg/Workspace/cpp/houjie/STL/iterator_catetory_output.png" alt="1569083607385" style="zoom: 80%;" />



## 3.iterator_category和type_traits对算法的影响

![1569085308237](/home/sxg/Workspace/cpp/houjie/STL/traits.png)



## 4.STL中的accumulate算法的应用

**程式**:

```c++
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
```

输出结果：

test accumulate()...........
using default accumulate:160
using functional's minus:40
using custom function:220
using custom object:280



## 5.STL算法for_each

源码：

```c++
template <class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f) {
	for (; first != last; ++first) {
		f(*first);
	}
	return f;
}
```







## 6. STL的replace，replace_if, replace_copy

![1569125938029](/home/sxg/Workspace/cpp/houjie/STL/replace.png)



## 7. STL的count,count_if

![1569126269529](/home/sxg/Workspace/cpp/houjie/STL/count.png)



## 8. STL的find,find_if

![1569126314303](/home/sxg/Workspace/cpp/houjie/STL/find.png)



## 9.STL的sort

![1569126358998](/home/sxg/Workspace/cpp/houjie/STL/sort.png)

**注:8个关联式容器原本就是已经排序了的**



## 10. C++中将bool类型用true、false输出设置

例如：cout << std::boolalpha << bool_flag << endl;



## 11. 仿函数(Functor)和函数对象

* 标准库里的实现

  ![1569128716080](/home/sxg/Workspace/cpp/houjie/STL/functor.png)

![1569132026742](/home/sxg/Workspace/cpp/houjie/STL/unary_binary.png)



## 12.函数适配器:binder2nd

STL中存在多种adapter：

![1569132935071](/home/sxg/Workspace/cpp/houjie/STL/adapters.png)

函数适配器：

![1569132997053](/home/sxg/Workspace/cpp/houjie/STL/functors.png)

**细节：**

```c++
typedef typename Operation::second_argument_type arg2_type

```

其中的typename为了告诉编译器其后的Operation::second_argument_type是一个类型！！！



## 13. 函数适配器：not1

![1569150359969](/home/sxg/Workspace/cpp/houjie/STL/not1.png)



## 14. 新型适配器bind(Since C++11)

![1569152086186](/home/sxg/Workspace/cpp/houjie/STL/bind.png)

**Test Case**:

```c++
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
```



## 15. 迭代器适配器inserter

![1569154136038](/home/sxg/Workspace/cpp/houjie/STL/insertor.png)

**太巧妙了:inserter辅助函数内部又调用insert_iterator，insert_iterator对=实现了操作符重载，改变了copy的=！！！**



## 16. X 适配器：ostream_iterator

标准库里的代码实现太完美了！

![1569245548476](/home/sxg/Workspace/cpp/houjie/STL/ostream_iterator.png)



## 17. X适配器：istream_iterator

![1569246491617](/home/sxg/Workspace/cpp/houjie/STL/istream_iterator.png)

## 18. tuple

![1569259481393](/home/sxg/Workspace/cpp/houjie/STL/tuple.png)



## 19. type traits

![1569259922100](/home/sxg/Workspace/cpp/houjie/STL/type_traits.png)



![1569284051528](/home/sxg/Workspace/cpp/houjie/STL/type__traits.png)

