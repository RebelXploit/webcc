#pragma once

namespace webcc
{
    // Minimal implementation of move/forward
    template<typename T> struct remove_reference { typedef T type; };
    template<typename T> struct remove_reference<T&> { typedef T type; };
    template<typename T> struct remove_reference<T&&> { typedef T type; };

    template<typename T>
    typename remove_reference<T>::type&& move(T&& t) {
        return static_cast<typename remove_reference<T>::type&&>(t);
    }

    template<typename T>
    T&& forward(typename remove_reference<T>::type& t) {
        return static_cast<T&&>(t);
    }
    template<typename T>
    T&& forward(typename remove_reference<T>::type&& t) {
        return static_cast<T&&>(t);
    }

    template<typename T>
    void swap(T& a, T& b)
    {
        T temp = move(a);
        a = move(b);
        b = move(temp);
    }
} // namespace webcc
