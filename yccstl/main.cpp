#include<iostream>
#include <concepts>

#include "utils/utils.h"
#include "iterator/iterator.h"
#include "allocator/construct.h"
#include "allocator/allocator.h"

int main() {
    yccstl::iterator<int, int> iterator;
    yccstl::allocator<int> alloc;

    int* int_ptr = yccstl::allocator<int>::allocate();
}
