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

