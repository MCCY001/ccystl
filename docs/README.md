# YCCSTL: A SIMPLIFIED STL MADE BY YCC

## 介绍（Intro）

yccstl 是一个简化版的 C++ 标准模板库（STL），设计用来提供 STL 的基本功能，如容器、迭代器、算法、适配器、函数对象和内存分配器。此库充分利用了现代 C++ 特性，包括智能指针以安全管理内存，模板和模板元编程来提高代码的类型安全性和灵活性，以及 lambda 表达式来简化函数定义。

yccstl 包含六大核心组件，每个都承担特定职能：容器（container）提供数据存储机制，如向量和列表，支持动态数据结构的管理；算法（algorithm）包括各种操作数据的方法，如排序和搜索；迭代器（iterator）作为连接容器与算法的桥梁，允许顺序访问容器中的元素；适配器（adapter）将容器转化为特定的数据结构，如栈和队列；函数对象（functor）用于封装函数或行为，如比较和执行操作；内存分配器负责高效地分配和管理内存资源。关于这六个组件的详细介绍可见该项目下对应的  intro 文件。实现这些组件的源代码以文件夹为单位分别存在 yccstl/. 中，以下是这些组件对应的头文件的名称。

后续会编写相应的测试文件来测试 yccstl 处理数据的性能。

## 容器（yccstl/container）

## 算法（yccstl/algorithm）

- `"algobase.h"`
- `"algo.h"`（待完成）

## 迭代器（yccstl/iterator）

## 适配器（yccstl/adapter）

## 函数对象（yccstl/functor）

## 内存分配器（yccstl/allocator）

- `"allocator.h"`
- `"construct.h"`

## 通用（yccstl/utils）

- `"utils.h"`
- `"type_traits.h"`
- `"exceptdef.h"`
- `"functional.h"`
