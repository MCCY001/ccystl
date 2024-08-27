#ifndef YCCSTL_UTILS_H_
#define YCCSTL_UTILS_H_

#include <cstddef>

#include "internal/type_traits.h"

namespace yccstl {

    // 加 typename 的目的是为了让编译器识别std::remove_reference<T>::type&&是一个类型而非静态成员变量

    // 移动语义
    template<class T>
    typename std::remove_reference<T>::type&& move(T&& arg) noexcept {
        return static_cast<typename std::remove_reference<T>::type&&>(arg);
    }

    // T&&利用了forwarding reference的性质，传入参数为左值时T推导成左值引用（int&），为右值时T推导成对应类型(int)，
    // 之后利用引用折叠实现完美转发

    // 完美转发左值
    template<class T>
    T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
        return static_cast<T&&>(arg);
    }

    // 完美转发右值
    template<class T>
    T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
        static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
        return static_cast<T&&>(arg);
    }

    // Tp: type parameter

    // 利用移动语义交换资源
    template<class Tp>
    void swap(Tp& lhs, Tp& rhs) {
        auto tmp = (yccstl::move(lhs));
        lhs = yccstl::move(rhs);
        rhs = yccstl::move(tmp);
    }

    template<class ForwardIter1, class ForwardIter2>
    ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2) {
        for (;first1 != last1; ++first1, (void)++first2) {
            yccstl::swap(*first1, *first2);
        }
        return first2;
    }

    template<class Tp, size_t N>
    void swap(Tp(&a)[N], Tp(&b)[N]) {
        yccstl::swap_range(a, a + N, b);
    }

    // pair

    template<class Ty1, class Ty2>
    struct pair {
        using first_type = Ty1;
        using second_type = Ty2;

        first_type first;
        second_type second;

        // 使用了未命名的模板参数
        // 基于 SFINAE（Substitution Failure Is Not An Error）原则

        // 默认构造函数
        template<class Other1 = Ty1, class Other2 = Ty2,
            typename std::enable_if <
            std::is_default_constructible<Other1>::value&&
            std::is_default_constructible<Other2>::value, int>::type = 0>
        constexpr pair() :first(), second() {
        }

        // 隐式构造函数
        template<class U1 = Ty1, class U2 = Ty2,
            typename std::enable_if<
            std::is_copy_constructible<U1>::value&&
            std::is_copy_constructible<U2>::value&&
            std::is_convertible<const U1&, Ty1>::value&&
            std::is_convertible<const U2&, Ty2>::value, int>::type = 0>
        constexpr pair(const Ty1& a, const Ty2& b) :first(a), second(b) {
        }

        // 显式构造函数
        template <class U1 = Ty1, class U2 = Ty2,
            typename std::enable_if<
            std::is_copy_constructible<U1>::value&&
            std::is_copy_constructible<U2>::value &&
            (!std::is_convertible<const U1&, Ty1>::value ||
                !std::is_convertible<const U2&, Ty2>::value), int>::type = 0>
        explicit constexpr pair(const Ty1& a, const Ty2& b)
            : first(a), second(b) {
        }

        pair(const pair& rhs) = default;
        pair(pair&& rhs) = default;

        // 隐式移动构造函数
        template <class Other1, class Other2,
            typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value&&
            std::is_constructible<Ty2, Other2>::value&&
            std::is_convertible<Other1&&, Ty1>::value&&
            std::is_convertible<Other2&&, Ty2>::value, int>::type = 0>
        constexpr pair(Other1&& a, Other2&& b)
            : first(yccstl::forward<Other1>(a)),
            second(yccstl::forward<Other2>(b)) {
        }

        // 显式移动构造函数
        template <class Other1, class Other2,
            typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value&&
            std::is_constructible<Ty2, Other2>::value &&
            (!std::is_convertible<Other1, Ty1>::value ||
                !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
        explicit constexpr pair(Other1&& a, Other2&& b)
            : first(yccstl::forward<Other1>(a)),
            second(yccstl::forward<Other2>(b)) {
        }

        // 隐式拷贝构造函数
        template <class Other1, class Other2,
            typename std::enable_if<
            std::is_constructible<Ty1, const Other1&>::value&&
            std::is_constructible<Ty2, const Other2&>::value&&
            std::is_convertible<const Other1&, Ty1>::value&&
            std::is_convertible<const Other2&, Ty2>::value, int>::type = 0>
        constexpr pair(const pair<Other1, Other2>& other)
            : first(other.first),
            second(other.second) {
        }

        // 显式拷贝构造函数
        template<class Other1, class Other2,
            typename std::enable_if<
            std::is_constructible<Ty1, const Other1&>::value&&
            std::is_constructible<Ty2, const Other2&>::value &&
            (!std::is_convertible<const Other1&, Ty1>::value ||
                !std::is_convertible<const Other2&, Ty2>::value), int>::type = 0>
        explicit constexpr pair(const pair<Other1, Other2>& other) :first(other.first), second(other.second) {
        }

        // 隐式移动构造函数
        template <class Other1, class Other2,
            typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value&&
            std::is_constructible<Ty2, Other2>::value&&
            std::is_convertible<Other1, Ty1>::value&&
            std::is_convertible<Other2, Ty2>::value, int>::type = 0>
        constexpr pair(pair<Other1, Other2>&& other)
            : first(yccstl::forward<Other1>(other.first)),
            second(yccstl::forward<Other2>(other.second)) {
        }

        // 显式移动构造函数
        template <class Other1, class Other2,
            typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value&&
            std::is_constructible<Ty2, Other2>::value &&
            (!std::is_convertible<Other1, Ty1>::value ||
                !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
        explicit constexpr pair(pair<Other1, Other2>&& other)
            : first(yccstl::forward<Other1>(other.first)),
            second(yccstl::forward<Other2>(other.second)) {
        }

        pair& operator=(const pair& rhs) {
            if (this != &rhs) {
                first = rhs.first;
                second = rhs.second;
            }
            return *this;
        }

        pair& operator=(pair&& rhs) {
            if (this != &rhs) {
                first = yccstl::move(rhs.first);
                second = yccstl::move(rhs.second);
            }
            return *this;
        }

        ~pair() = default;

        void swap(pair& other) {
            if (this != other) {
                yccstl::swap(first, other.first);
                yccstl::swap(second, other.second);
            }
        }
    };

    template<class Ty1, class Ty2>
    bool operator==(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<class Ty1, class Ty2>
    bool operator<(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs) {
        return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
    }

    template <class Ty1, class Ty2>
    bool operator!=(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs) {
        return !(lhs == rhs);
    }

    template <class Ty1, class Ty2>
    bool operator>(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs) {
        return rhs < lhs;
    }

    template <class Ty1, class Ty2>
    bool operator<=(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs) {
        return !(rhs < lhs);
    }

    template <class Ty1, class Ty2>
    bool operator>=(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs) {
        return !(lhs < rhs);
    }

    template<class Ty1, class Ty2>
    void swap(pair<Ty1, Ty2>& lhs, pair<Ty1, Ty2>& rhs) {
        lhs.swap(rhs);
    }

    template<class Ty1, class Ty2>
    pair<Ty1, Ty2> make_pair(Ty1&& first, Ty2&& second) {
        return pair<Ty1, Ty2>(yccstl::forward<Ty1>(first), yccstl::forward<Ty2>(second));
    }
}

#endif // !YCCSTL_UTILS_H_