#include<iostream>
#include "utils/utils.h"

template<typename T>
void print(T& t) {
    std::cout << "lvalue" << std::endl;
}

template<typename T>
void print(T&& t) {
    std::cout << "rvalue" << std::endl;
}

template<typename T>
void testForward(T&& v) {
    print(yccstl::forward<int>(1));
    print(v);
    print(yccstl::forward<T>(v));
    print(yccstl::move(v));
}

int main() {
    testForward(1);
    std::cout << "======================" << std::endl;
    int x = 1;
    testForward(x);
    return 0;
}
