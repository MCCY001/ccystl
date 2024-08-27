#ifndef CCYSTL_FUNCTIONAL_H_
#define CCYSTL_FUNCTIONAL_H_

// 这个头文件包含了 ccystl 的函数对象与哈希函数

#include <cstddef>

namespace ccystl {
    // 定义一元函数的参数型别和返回值型别
    template<typename Arg, typename Result>
    struct unarg_function {
        typedef Arg argument_type;
        typedef Result result_type;
    };

    // 定义二元函数的参数型别的返回值型别
    template <typename Arg1, typename Arg2, typename Result>
    struct binary_function {
        typedef Arg1      first_argument_type;
        typedef Arg2      second_argument_type;
        typedef Result    result_type;
    };

    // 函数对象：加法
    template<typename T>
    struct plus :public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) {
            return x + y;
        }
    };

    // 函数对象：减法
    template <typename T>
    struct minus :public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) const { return x - y; }
    };

    // 函数对象：乘法
    template <typename T>
    struct multiplies :public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) const { return x * y; }
    };

    // 函数对象：除法
    template <typename T>
    struct divides :public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) const { return x / y; }
    };

    // 函数对象：模取
    template <typename T>
    struct modulus :public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) const { return x % y; }
    };

    // 函数对象：否定
    template <typename T>
    struct negate :public unarg_function<T, T> {
        T operator()(const T& x) const { return -x; }
    };

    // 函数对象：等于
    template <typename T>
    struct equal_to :public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x == y; }
    };

    // 函数对象：不等于
    template <typename T>
    struct not_equal_to :public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x != y; }
    };

    // 函数对象：大于
    template <typename T>
    struct greater :public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x > y; }
    };

    // 函数对象：小于
    template <typename T>
    struct less :public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x < y; }
    };

    // 函数对象：大于等于
    template <typename T>
    struct greater_equal :public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x >= y; }
    };

    // 函数对象：小于等于
    template <typename T>
    struct less_equal :public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x <= y; }
    };

    // 函数对象：逻辑与
    template <typename T>
    struct logical_and :public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x && y; }
    };

    // 函数对象：逻辑或
    template <typename T>
    struct logical_or :public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x || y; }
    };

    // 函数对象：逻辑非
    template <typename T>
    struct logical_not :public unarg_function<T, bool> {
        bool operator()(const T& x) const { return !x; }
    };

    // 加法的单位元，plus为仿函数对象
    template <typename T>
    T identity_element(plus<T>) { return T(0); }

    // 乘法的单位元，multiplies为仿函数对象
    template <typename T>
    T identity_element(multiplies<T>) { return T(1); }

    // 证同函数：不会改变元素，返回本身
    template <typename T>
    struct identity :public unarg_function<T, bool> {
        const T& operator()(const T& x) const { return x; }
    };

    // 选择函数：接受一个 pair，返回第一个元素
    template <typename Pair>
    struct selectfirst :public unarg_function<Pair, typename Pair::first_type> {
        const typename Pair::first_type& operator()(const Pair& x) const {
            return x.first;
        }
    };

    // 选择函数：接受一个 pair，返回第二个元素
    template <typename Pair>
    struct selectsecond :public unarg_function<Pair, typename Pair::second_type> {
        const typename Pair::second_type& operator()(const Pair& x) const {
            return x.second;
        }
    };

    // 投射函数：返回第一参数
    template <typename Arg1, typename Arg2>
    struct projectfirst :public binary_function<Arg1, Arg2, Arg1> {
        Arg1 operator()(const Arg1& x, const Arg2&) const { return x; }
    };

    // 投射函数：返回第二参数
    template <typename Arg1, typename Arg2>
    struct projectsecond :public binary_function<Arg1, Arg2, Arg1> {
        Arg2 operator()(const Arg1&, const Arg2& y) const { return y; }
    };

    /*****************************************************************************************/
    // 哈希函数对象

    // 对于大部分类型，hash function 什么都不做
    template <typename Key>
    struct hash {};

    // 针对指针的偏特化版本
    template<typename T>
    struct hash<T*> {
        size_t operator()(T* p) const noexcept {
            return reinterpret_cast<size_t>(p);
        }
    };

    // 哈希函数 
    // 对于 整型数据（如 int, unsigned int, char 等）,
    // 直接返回原值（通过 static_cast<size_t>(val) 转换）
#define CCYSTL_TRIVIAL_HASH_FCN(Type)                 \
    template<>                                        \
    struct hash<Type> {                               \
        size_t operator()(Type val) const noexcept {  \
    return static_cast<size_t>(val); }                \
    };

    CCYSTL_TRIVIAL_HASH_FCN(bool)

        CCYSTL_TRIVIAL_HASH_FCN(char)

        CCYSTL_TRIVIAL_HASH_FCN(signed char)

        CCYSTL_TRIVIAL_HASH_FCN(unsigned char)

        CCYSTL_TRIVIAL_HASH_FCN(wchar_t)

        CCYSTL_TRIVIAL_HASH_FCN(char16_t)

        CCYSTL_TRIVIAL_HASH_FCN(char32_t)

        CCYSTL_TRIVIAL_HASH_FCN(short)

        CCYSTL_TRIVIAL_HASH_FCN(unsigned short)

        CCYSTL_TRIVIAL_HASH_FCN(int)

        CCYSTL_TRIVIAL_HASH_FCN(unsigned int)

        CCYSTL_TRIVIAL_HASH_FCN(long)

        CCYSTL_TRIVIAL_HASH_FCN(unsigned long)

        CCYSTL_TRIVIAL_HASH_FCN(long long)

        CCYSTL_TRIVIAL_HASH_FCN(unsigned long long)

#undef CCYSTL_TRIVIAL_HASH_FCN


        // 对于浮点数，逐位哈希
        // FNV-1a 哈希算法，
        // 一种非常常见的非加密哈希算法，用于生成高效的哈希值。
        // 该算法通过逐字节处理数据、异或操作以及乘以一个素数来生成哈希值，
        inline size_t bitwise_hash(const unsigned char* first, size_t count) {
#if (_MSC_VER && _WIN64) || ((__GNUC__ || __clang__) &&__SIZEOF_POINTER__ == 8)
        const size_t fnv_offset = 14695981039346656037ull;
        const size_t fnv_prime = 1099511628211ull;
#else
        const size_t fnv_offset = 2166136261u;
        const size_t fnv_prime = 16777619u;
#endif
        size_t result = fnv_offset;
        for (size_t i = 0; i < count; ++i) {
            result ^= (size_t)first[i];
            result *= fnv_prime;
        }
        return result;
    }

    template <>
    struct hash<float> {
        size_t operator()(const float& val) {
            return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(float));
        }
    };

    template <>
    struct hash<double> {
        size_t operator()(const double& val) {
            return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(double));
        }
    };

    template <>
    struct hash<long double> {
        size_t operator()(const long double& val) {
            return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(long double));
        }
    };
} // namespace ccystl

#endif // !CCYSTL_FUNCTIONAL_H_