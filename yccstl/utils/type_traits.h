#ifndef YCCSTL_TYPE_TRAITS_H_
#define YCCSTL_TYPE_TRAITS_H_

#include <type_traits>

namespace yccstl {
    template<class T, T v>
    struct y_integral_constant {
        static constexpr T value = v;
    };

    template<bool b>
    using y_bool_constant = y_integral_constant<bool, b>;

    typedef y_bool_constant<true> y_true_type;
    typedef y_bool_constant<false> y_false_type;

    // type traits for pair

    template<class T1, class T2>
    struct pair;

    template<class T>
    struct is_pair :yccstl::y_false_type {};

    template<class T1, class T2>
    struct is_pair<yccstl::pair<T1, T2>> :yccstl::y_true_type {};


} // namespace yccstl


#endif // !YCCSTL_TYPE_TRAITS_H_