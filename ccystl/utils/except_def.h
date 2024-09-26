#ifndef CCYSTL_EXCEPT_DEF_H_
#define CCYSTL_EXCEPT_DEF_H_

/**
 * @file except_def.h
 * @brief 该头文件定义了一些用于异常处理的宏，供 ccystl 库使用。
 *
 * 包含用于长度错误、越界错误、运行时错误等异常的宏定义，
 * 以及调试断言宏，方便在代码中进行错误检查和调试。
 */

#include <cassert>   ///< 引入断言头文件，用于调试检查
#include <stdexcept> ///< 引入标准异常类头文件

namespace ccystl {

/**
 * @def CCYSTL_DEBUG(expr)
 * @brief 调试宏，用于在调试模式下执行断言检查。
 *
 * 通过 assert 对表达式进行检查，在调试模式下如果表达式为假，
 * 程序将中断并显示断言失败的信息。此宏在发布版本中不会生效。
 *
 * @param expr 需要检查的表达式。
 *
 * 示例：
 * @code
 * CCYSTL_DEBUG(ptr != nullptr);  // 检查指针是否为空
 * @endcode
 */
#define CCYSTL_DEBUG(expr) assert(expr)

/**
 * @def THROW_LENGTH_ERROR_IF(expr, what)
 * @brief 长度错误异常宏，用于在表达式为真时抛出 std::length_error 异常。
 *
 * 当 `expr` 为真时抛出一个包含 `what` 作为错误信息的 `std::length_error` 异常。
 * 这个宏常用于检查容器大小是否超出允许范围。
 *
 * @param expr 触发异常的条件表达式。
 * @param what 异常的错误信息字符串。
 *
 * 示例：
 * @code
 * THROW_LENGTH_ERROR_IF(size > max_size, "size exceeds maximum allowed size");
 * @endcode
 */
#define THROW_LENGTH_ERROR_IF(expr, what)                                      \
  if ((expr))                                                                  \
  throw std::length_error((what))

/**
 * @def THROW_OUT_OF_RANGE_IF(expr, what)
 * @brief 越界错误异常宏，用于在表达式为真时抛出 std::out_of_range 异常。
 *
 * 当 `expr` 为真时抛出一个包含 `what` 作为错误信息的 `std::out_of_range` 异常。
 * 这个宏通常用于检查访问的索引是否超出容器的范围。
 *
 * @param expr 触发异常的条件表达式。
 * @param what 异常的错误信息字符串。
 *
 * 示例：
 * @code
 * THROW_OUT_OF_RANGE_IF(index >= vec.size(), "index is out of range");
 * @endcode
 */
#define THROW_OUT_OF_RANGE_IF(expr, what)                                      \
  if ((expr))                                                                  \
  throw std::out_of_range((what))

/**
 * @def THROW_RUNTIME_ERROR_IF(expr, what)
 * @brief 运行时错误异常宏，用于在表达式为真时抛出 std::runtime_error 异常。
 *
 * 当 `expr` 为真时抛出一个包含 `what` 作为错误信息的 `std::runtime_error` 异常。
      * 这个宏适用于通用的运行时错误检查。
      *
      * @param expr 触发异常的条件表达式。
      * @param what 异常的错误信息字符串。
      *
      * 示例：
      * @code
      * THROW_RUNTIME_ERROR_IF(!file.is_open(), "failed to open file");
      * @endcode
      */
#define THROW_RUNTIME_ERROR_IF(expr, what) \
  if ((expr)) throw std::runtime_error((what))

} // namespace ccystl

#endif // !CCYSTL_EXCEPT_DEF_H_
