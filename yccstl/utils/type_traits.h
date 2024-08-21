#ifndef YCCSTL_TYPE_TRAITS_H_
#define YCCSTL_TYPE_TRAITS_H_

#include <type_traits>

namespace yccstl {
    template<class T, T v>
    struct y_integral_constant {
        static constexpr T value = v;
        using value_type = T;
        using type = y_integral_constant;

        // 常量转换操作符，将y_integral_constant类型转换成value_type类型
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

    template<bool b>
    using y_bool_constant = y_integral_constant<bool, b>;

    using y_true_type = y_bool_constant<true>;
    using y_false_type = y_bool_constant<false>;

    // type traits for pair

    template<class T1, class T2>
    struct pair;

    template<class T>
    struct is_pair :yccstl::y_false_type {};

    template<class T1, class T2>
    struct is_pair<yccstl::pair<T1, T2>> :yccstl::y_true_type {};
} // namespace yccstl


#endif // !YCCSTL_TYPE_TRAITS_H_