#ifndef CCYSTL_CONSTRUCT_H_
#define CCYSTL_CONSTRUCT_H_

#include <new>

#include "ccystl/internal/type_traits.h"
#include "ccystl/iterator/iterator.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)  // unused parameter
#endif // _MSC_VER

namespace ccystl {

    // 构造对象 placement new

    template<class Ty>
    void construct(Ty* ptr) {
        ::new ((void*)ptr) Ty();
    }

    template<class Ty1, class Ty2>
    void construct(Ty1* ptr, const Ty2& value) {
        ::new ((void*)ptr) Ty1(value);
    }

    // 析构对象

    template<class Ty, class... Args>
    void construct(Ty* ptr, Args&&... args) {
        ::new ((void*)ptr) Ty(ccystl::forward<Args>(args)...);
    }

    template<class Ty>
    void destroy_one(Ty*, std::true_type) {}

    template<class Ty>
    void destroy_one(Ty* pointer, std::false_type) {
        if (pointer != nullptr) {
            pointer->~Ty();
        }
    }

    template <class ForwardIter>
    void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

    template <class ForwardIter>
    void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
        for (; first != last; ++first)
            destory(&*first);
    }

    template <class Ty>
    void destroy(Ty* pointer) {
        destroy_one(pointer, std::is_trivially_destructible<Ty>{});
    }

    template <class ForwardIter>
    void destroy(ForwardIter first, ForwardIter last) {
        destroy_cat(first, last, std::is_trivially_destructible<
            typename iterator_traits<ForwardIter>::value_type>{});
    }

} // namespace ccystl

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif
