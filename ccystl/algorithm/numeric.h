#ifndef CCYSTL_NUMERIC_H_
#define CCYSTL_NUMERIC_H_

/**
 * @file numeric.h
 * @brief
 * 该头文件定义了一些常用的数值算法，如累加、相邻差值、内积计算、填充序列等。
 *
 * 这些算法提供了对数值序列进行处理的基本操作，可以用于各类容器和迭代器。
 */

namespace ccystl {
/**
 * @brief 对区间内的元素进行累加。
 *
 * 从初值 `init` 开始，将区间 `[first, last)` 内的每个元素累加到 `init` 上。
 *
 * @tparam InputIter 输入迭代器类型。
 * @tparam T 累加结果的类型。
 * @param first 输入区间的起始迭代器。
 * @param last 输入区间的结束迭代器。
 * @param init 累加的初始值。
 * @return T 返回累加后的结果。
 */
template <class InputIter, class T>
T accumulate(InputIter first, InputIter last, T init) {
    for (; first != last; ++first) {
        init += *first;
    }
    return init;
}

/**
 * @brief 对区间内的元素进行自定义操作的累加。
 *
 * 从初值 `init` 开始，使用自定义的二元操作 `binary_op` 将区间 `[first, last)`
 * 内的每个元素与 `init` 进行操作。
 *
 * @tparam InputIter 输入迭代器类型。
 * @tparam T 累加结果的类型。
 * @tparam BinaryOp 二元操作函数对象类型。
 * @param first 输入区间的起始迭代器。
 * @param last 输入区间的结束迭代器。
 * @param init 累加的初始值。
 * @param binary_op 自定义的二元操作函数对象。
 * @return T 返回累加后的结果。
 */
template <class InputIter, class T, class BinaryOp>
T accumulate(InputIter first, InputIter last, T init, BinaryOp binary_op) {
    for (; first != last; ++first) {
        init = binary_op(init, *first);
    }
    return init;
}

/**
 * @brief 计算相邻元素的差值并将结果保存到输出区间。
 *
 * 计算输入区间 `[first, last)` 中每对相邻元素的差值，结果保存到以 `result`
 * 为起始的输出区间。
 *
 * @tparam InputIter 输入迭代器类型。
 * @tparam OutputIter 输出迭代器类型。
 * @param first 输入区间的起始迭代器。
 * @param last 输入区间的结束迭代器。
 * @param result 输出区间的起始迭代器。
 * @return OutputIter 返回输出区间的结束迭代器。
 */
template <class InputIter, class OutputIter>
OutputIter adjacent_difference(InputIter first, InputIter last,
                               OutputIter result) {
    if (first == last)
        return result;
    *result = *first; // 记录第一个元素
    auto value = *first;
    while (++first != last) {
        auto tmp = *first;
        *++result = tmp - value;
        value = tmp;
    }
    return ++result;
}

/**
 * @brief 使用自定义操作计算相邻元素的差值并将结果保存到输出区间。
 *
 * 计算输入区间 `[first, last)` 中每对相邻元素的自定义二元操作结果，结果保存到以
 * `result` 为起始的输出区间。
 *
 * @tparam InputIter 输入迭代器类型。
 * @tparam OutputIter 输出迭代器类型。
 * @tparam BinaryOp 二元操作函数对象类型。
 * @param first 输入区间的起始迭代器。
 * @param last 输入区间的结束迭代器。
 * @param result 输出区间的起始迭代器。
 * @param binary_op 自定义的二元操作函数对象。
 * @return OutputIter 返回输出区间的结束迭代器。
 */
template <class InputIter, class OutputIter, class BinaryOp>
OutputIter adjacent_difference(InputIter first, InputIter last,
                               OutputIter result, BinaryOp binary_op) {
    if (first == last)
        return result;
    *result = *first; // 记录第一个元素
    auto value = *first;
    while (++first != last) {
        auto tmp = *first;
        *++result = binary_op(tmp, value);
        value = tmp;
    }
    return ++result;
}

/**
 * @brief 计算两个区间的内积。
 *
 * 从初值 `init` 开始，计算区间 `[first1, last1)` 和 `[first2, first2 + (last1 -
 * first1))` 的内积。
 *
 * @tparam InputIter1 第一个输入区间的迭代器类型。
 * @tparam InputIter2 第二个输入区间的迭代器类型。
 * @tparam T 内积结果的类型。
 * @param first1 第一个输入区间的起始迭代器。
 * @param last1 第一个输入区间的结束迭代器。
 * @param first2 第二个输入区间的起始迭代器。
 * @param init 内积的初始值。
 * @return T 返回内积计算的结果。
 */
template <class InputIter1, class InputIter2, class T>
T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2,
                T init) {
    for (; first1 != last1; ++first1, ++first2) {
        init += (*first1 * *first2);
    }
    return init;
}

/**
 * @brief 使用自定义操作计算两个区间的内积。
 *
 * 从初值 `init` 开始，使用自定义的加法和乘法操作计算区间 `[first1, last1)` 和
 * `[first2, first2 + (last1 - first1))` 的内积。
 *
 * @tparam InputIter1 第一个输入区间的迭代器类型。
 * @tparam InputIter2 第二个输入区间的迭代器类型。
 * @tparam T 内积结果的类型。
 * @tparam BinaryOp1 自定义的加法操作函数对象类型。
 * @tparam BinaryOp2 自定义的乘法操作函数对象类型。
 * @param first1 第一个输入区间的起始迭代器。
 * @param last1 第一个输入区间的结束迭代器。
 * @param first2 第二个输入区间的起始迭代器。
 * @param init 内积的初始值。
 * @param binary_op1 自定义的加法操作函数对象。
 * @param binary_op2 自定义的乘法操作函数对象。
 * @return T 返回内积计算的结果。
 */
template <class InputIter1, class InputIter2, class T, class BinaryOp1,
          class BinaryOp2>
T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init,
                BinaryOp1 binary_op1, BinaryOp2 binary_op2) {
    for (; first1 != last1; ++first1, ++first2) {
        init = binary_op1(init, binary_op2(*first1, *first2));
    }
    return init;
}

/**
 * @brief 填充区间 `[first, last)`，以 `value` 为初始值开始递增。
 *
 * 从初值 `value` 开始，对区间 `[first, last)` 的每个元素递增赋值。
 *
 * @tparam ForwardIter 前向迭代器类型。
 * @tparam T 递增值的类型。
 * @param first 要填充的区间的起始迭代器。
 * @param last 要填充的区间的结束迭代器。
 * @param value 填充的初始值。
 */
template <class ForwardIter, class T>
void iota(ForwardIter first, ForwardIter last, T value) {
    while (first != last) {
        *first++ = value;
        ++value;
    }
}

/**
 * @brief 计算局部累计和，将结果保存到输出区间。
 *
 * 计算输入区间 `[first, last)` 的局部累计和，结果保存到以 `result`
 * 为起始的输出区间。
 *
 * @tparam InputIter 输入迭代器类型。
 * @tparam OutputIter 输出迭代器类型。
 * @param first 输入区间的起始迭代器。
 * @param last 输入区间的结束迭代器。
 * @param result 输出区间的起始迭代器。
 * @return OutputIter 返回输出区间的结束迭代器。
 */
template <class InputIter, class OutputIter>
OutputIter partial_sum(InputIter first, InputIter last, OutputIter result) {
    if (first == last)
        return result;
    *result = *first; // 记录第一个元素
    auto value = *first;
    while (++first != last) {
        value = value + *first;
        *++result = value;
    }
    return ++result;
}

/**
 * @brief 使用自定义操作计算局部累计，将结果保存到输出区间。
 *
 * 使用自定义的二元操作计算输入区间 `[first, last)` 的局部累计，结果保存到以 `result` 为起始的输出区间。
 *
 * @tparam InputIter 输入迭代器类型。
 * @tparam OutputIter 输出迭代器类型。
 * @tparam BinaryOp 二元操作函数对象类型。
 * @param first 输入区间的起始迭代器。
 * @param last 输入区间的结束迭代器。
 * @param result 输出区间的起始迭代器。
 * @param binary_op 自定义的二元操作函数对象。
 * @return OutputIter 返回输出区间的结束迭代器。
 */
template <class InputIter, class OutputIter, class BinaryOp>
OutputIter partial_sum(InputIter first, InputIter last, OutputIter result, BinaryOp binary_op) {
    if (first == last) return result;
    *result = *first; // 记录第一个元素
    auto value = *first;
    while (++first != last) {
        value = binary_op(value, *first);
        *++result = value;
    }
    return ++result;
}
} // namespace ccystl

#endif // !CCYSTL_NUMERIC_H_
