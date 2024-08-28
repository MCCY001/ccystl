#ifndef CCYSTL_SET_ALGO_H_
#define CCYSTL_SET_ALGO_H_

#include "ccystl/iterator/iterator.h"
#include "ccystl/algorithm/algobase.h"

// 这个头文件包含 set 的四种算法: union, intersection, difference, symmetric_difference
// 所有函数都要求序列有序

namespace ccystl {

    /*
    计算交集 S1∪S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    */
    template<class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_union(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                *result = *first1;
                ++first1;
            }
            else if (*first1 > *first2) {
                *result = *first2;
                ++first1;
            }
            else {
                *result = *first1;
                ++first1;
                ++first2;
            }
            ++result;
        }
        return ccystl::copy(first2, last2, ccystl::copy(first1, last1, result));
    }

    template<class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_union(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *result = *first1;
                ++first1;
            }
            else if (comp(*first2, *first1)) {
                *result = *first2;
                ++first1;
            }
            else {
                *result = *first1;
                ++first1;
                ++first2;
            }
            ++result;
        }
        return ccystl::copy(first2, last2, ccystl::copy(first1, last1, result));
    }

    /*
    计算并集 S1∩S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    */
    template<class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_intersection(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                ++first1;
            }
            else if (*first2 < *first1) {
                ++first2;
            }
            else {
                *result = *first1;
                ++first1;
                ++first2;
                ++result;
            }
        }
        return result;
    }

    template<class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_intersection(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                ++first1;
            }
            else if (comp(*first2, *first1)) {
                ++first2;
            }
            else {
                *result = *first1;
                ++first1;
                ++first2;
                ++result;
            }
        }
        return result;
    }

    /*
    计算差集 S1-S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    差集表示的是：在第一个范围中存在但不在第二个范围中的元素。
    */
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_difference(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                *result = *first1;
                ++first1;
                ++result;
            }
            else if (*first2 < *first1) {
                ++first2;
            }
            else {
                ++first1;
                ++first2;
            }
        }
        return ccystl::copy(first1, last1, result);
    }

    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_difference(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *result = *first1;
                ++first1;
                ++result;
            }
            else if (comp(*first2, *first1)) {
                ++first2;
            }
            else {
                ++first1;
                ++first2;
            }
        }
        return ccystl::copy(first1, last1, result);
    }

    /*
    计算对称差集 (S1-S2)∪(S2-S1) 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    对称差集包括只存在一个集合中的元素。
    */
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_symmetric_difference(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                *result = *first1;
                ++first1;
                ++result;
            }
            else if (*first2 < *first1) {
                *result = *first2;
                ++first2;
                ++result;
            }
            else {
                ++first1;
                ++first2;
            }
        }
        return ccystl::copy(first2, last2, ccystl::copy(first1, last1, result));
    }

    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_symmetric_difference(
        InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *result = *first1;
                ++first1;
                ++result;
            }
            else if (comp(*first2, *first1)) {
                *result = *first2;
                ++first2;
                ++result;
            }
            else {
                ++first1;
                ++first2;
            }
        }
        return ccystl::copy(first2, last2, ccystl::copy(first1, last1, result));
    }
} // namespace ccystl
#endif // !CCY_SET_ALGO_H_