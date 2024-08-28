#ifndef CCYSTL_ASTRING_H_
#define CCYSTL_ASTRING_H_

// 定义了 string, wstring, u16string, u32string 类型

#include "ccystl/container/sequence_container/basic_string.h"

namespace ccystl {

    using string = ccystl::basic_string<char>;
    using wstring = ccystl::basic_string<wchar_t>;
    using u16string = ccystl::basic_string<char16_t>;
    using u32string = ccystl::basic_string<char32_t>;

}
#endif // !CCYSTL_ASTRING_H_

