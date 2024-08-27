#include <iostream>
#include <concepts>
#include <exception>

#include "utils/utils.h"
#include "utils/exceptdef.h"

#include "iterator/iterator.h"

#include "allocator/construct.h"
#include "allocator/allocator.h"

#include "algorithm/algobase.h"
#include "algorithm/algo.h"
#include "algorithm/numeric.h"

#include "functor/functional.h"

int main() {
    ccystl::iterator<int, int> iterator;
    ccystl::allocator<int> alloc;

    int* int_ptr = ccystl::allocator<int>::allocate();
}
