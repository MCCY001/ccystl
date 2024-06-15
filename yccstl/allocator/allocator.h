#ifndef YCCSTL_ALLOCATOR_H_
#define YCCSTL_ALLOCATOR_H_

#include "allocator/construct.h"
#include "utils/utils.h"

namespace yccstl {

    template <class T>
    class allocator {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

    public:
        static T* allocate();
        static T* allocate(size_type n);

        static void deallocate(T* ptr);
        static void deallocate(T* ptr, size_type n);

        static void construct(T* ptr);
        static void construct(T* ptr, const T& value);
        static void construct(T* ptr, T&& value);

        template<class... Args>
        static void construct(T* ptr, Args&& ...args);

        static void destroy(T* ptr);
        static void destroy(T* first, T* last);
    };

    template <class T>
    T* allocator<T>::allocate() {
        return static_cast<T*>(::operator new(sizeof(T)));
    }

    template <class T>
    T* allocator<T>::allocate(size_type n) {
        if (n == 0)
            return nullptr;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    template <class T>
    void allocator<T>::deallocate(T* ptr) {
        if (ptr == nullptr)
            return;
        ::operator delete(ptr);
    }

    template <class T>
    void allocator<T>::deallocate(T* ptr, size_type /*size*/) {
        if (ptr == nullptr)
            return;
        ::operator delete(ptr);
    }

    template <class T>
    void allocator<T>::construct(T* ptr) {
        yccstl::construct(ptr);
    }

    template <class T>
    void allocator<T>::construct(T* ptr, const T& value) {
        yccstl::construct(ptr, value);
    }

    template <class T>
    void allocator<T>::construct(T* ptr, T&& value) {
        yccstl::construct(ptr, yccstl::move(value));
    }

    template <class T>
    template <class ...Args>
    void allocator<T>::construct(T* ptr, Args&& ...args) {
        yccstl::construct(ptr, yccstl::forward<Args>(args)...);
    }

    template <class T>
    void allocator<T>::destroy(T* ptr) {
        yccstl::destroy(ptr);
    }

    template <class T>
    void allocator<T>::destroy(T* first, T* last) {
        yccstl::destroy(first, last);
    }

} // namespace yccstl

#endif