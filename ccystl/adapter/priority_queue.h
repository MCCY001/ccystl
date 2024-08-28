#ifndef CCYSTL_PRIORITY_QUEUE_H_
#define CCYSTL_PRIORITY_QUEUE_H_

// 这个头文件包含了模板类 priority_queue
// priority_queue : 优先队列

#include "ccystl/container/sequence_container/deque.h"
#include "ccystl/container/sequence_container/vector.h"
#include "ccystl/functor/functional.h"
#include "ccystl/algorithm/heap_algo.h"

namespace ccystl {

    // 模板类 priority_queue
    // 参数一代表数据类型，参数二代表容器类型，缺省使用 ccystl::vector 作为底层容器
    // 参数三代表比较权值的方式，缺省使用 ccystl::less 作为比较方式
    template <class T, class Container = ccystl::vector<T>,
        class Compare = ccystl::less<typename Container::value_type>>
        class priority_queue {
        public:
            typedef Container                           container_type;
            typedef Compare                             value_compare;
            // 使用底层容器的型别
            typedef typename Container::value_type      value_type;
            typedef typename Container::size_type       size_type;
            typedef typename Container::reference       reference;
            typedef typename Container::const_reference const_reference;

            static_assert(std::is_same<T, value_type>::value,
                "the value_type of Container should be same with T");

        private:
            container_type c_;     // 用底层容器来表现 priority_queue
            value_compare  comp_;  // 权值比较的标准

        public:
            // 构造、复制、移动函数
            priority_queue() = default;

            priority_queue(const Compare& c)
                :c_(), comp_(c) {
            }

            explicit priority_queue(size_type n)
                :c_(n) {
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
            }
            priority_queue(size_type n, const value_type& value)
                :c_(n, value) {
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
            }

            template <class IIter>
            priority_queue(IIter first, IIter last)
                : c_(first, last) {
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
            }

            priority_queue(std::initializer_list<T> ilist)
                :c_(ilist) {
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
            }

            priority_queue(const Container& s)
                :c_(s) {
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
            }
            priority_queue(Container&& s)
                :c_(ccystl::move(s)) {
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
            }

            priority_queue(const priority_queue& rhs)
                :c_(rhs.c_), comp_(rhs.comp_) {
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
            }
            priority_queue(priority_queue&& rhs)
                :c_(ccystl::move(rhs.c_)), comp_(rhs.comp_) {
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
            }

            priority_queue& operator=(const priority_queue& rhs) {
                c_ = rhs.c_;
                comp_ = rhs.comp_;
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
                return *this;
            }
            priority_queue& operator=(priority_queue&& rhs) {
                c_ = ccystl::move(rhs.c_);
                comp_ = rhs.comp_;
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
                return *this;
            }
            priority_queue& operator=(std::initializer_list<T> ilist) {
                c_ = ilist;
                comp_ = value_compare();
                ccystl::make_heap(c_.begin(), c_.end(), comp_);
                return *this;
            }

            ~priority_queue() = default;

        public:

            // 访问元素相关操作
            const_reference top() const { return c_.front(); }

            // 容量相关操作
            bool      empty() const noexcept { return c_.empty(); }
            size_type size()  const noexcept { return c_.size(); }

            // 修改容器相关操作
            template <class... Args>
            void emplace(Args&& ...args) {
                c_.emplace_back(ccystl::forward<Args>(args)...);
                ccystl::push_heap(c_.begin(), c_.end(), comp_);
            }

            void push(const value_type& value) {
                c_.push_back(value);
                ccystl::push_heap(c_.begin(), c_.end(), comp_);
            }
            void push(value_type&& value) {
                c_.push_back(ccystl::move(value));
                ccystl::push_heap(c_.begin(), c_.end(), comp_);
            }

            void pop() {
                ccystl::pop_heap(c_.begin(), c_.end(), comp_);
                c_.pop_back();
            }

            void clear() {
                while (!empty())
                    pop();
            }

            void swap(priority_queue& rhs) noexcept(noexcept(ccystl::swap(c_, rhs.c_)) &&
                noexcept(ccystl::swap(comp_, rhs.comp_))) {
                ccystl::swap(c_, rhs.c_);
                ccystl::swap(comp_, rhs.comp_);
            }

        public:
            friend bool operator==(const priority_queue& lhs, const priority_queue& rhs) {
                return lhs.c_ == rhs.c_;
            }
            friend bool operator!=(const priority_queue& lhs, const priority_queue& rhs) {
                return lhs.c_ != rhs.c_;
            }
    };

    // 重载比较操作符
    template <class T, class Container, class Compare>
    bool operator==(priority_queue<T, Container, Compare>& lhs,
        priority_queue<T, Container, Compare>& rhs) {
        return lhs == rhs;
    }

    template <class T, class Container, class Compare>
    bool operator!=(priority_queue<T, Container, Compare>& lhs,
        priority_queue<T, Container, Compare>& rhs) {
        return lhs != rhs;
    }

    // 重载 ccystl 的 swap
    template <class T, class Container, class Compare>
    void swap(priority_queue<T, Container, Compare>& lhs,
        priority_queue<T, Container, Compare>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
        lhs.swap(rhs);
    }

} // namespace ccystl
#endif // !CCYSTL_PRIORITY_QUEUE_H_

