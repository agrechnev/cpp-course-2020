#pragma once
// By Oleksiy Grechnyev

#include <cstddef>
#include <stdexcept>

// forward declarations for operator==
template <typename T, size_t N>
class MyArray;
/// Non-member operator== declaration
template <typename T1, size_t N1>
bool operator==(const MyArray<T1, N1> & lhs, const MyArray<T1, N1> & rhs);

/// My own implementation of std::array (more or less), but no reverse iterators !
template <typename T, size_t N>
class MyArray{
public: //=== Type definitions
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = T *;
    using const_iterator = const T *;

public: //=== Operators

    T & operator[] (std::size_t i){
        return dat[i];
    }
    const T & operator[] (std::size_t i) const {
        return dat[i];
    }

    // friend is not needed here, but we would need it if data was private
    friend bool operator==<T, N>(const MyArray<T, N> & lhs, const MyArray<T, N> & rhs);
public: //=== Methods
    /// assign from an iterator pair
    template <typename I>
    void assign(I begin, I end);

    // Idexing
    T & at(std::size_t i){
        checkRange(i);
        return dat[i];
    }
    const T & at(std::size_t i) const {
        checkRange(i);
        return dat[i];
    }

    // Fill with a value
    void fill(const T & val){
        for (T & e : dat)
            e = val;
    }

    // Misc methods
    std::size_t size(){
        return N;
    }

    bool empty(){
        return 0 == N;
    }

    T* data(){
        return dat;
    }


    // Iterators
    T* begin(){
        return dat;
    }
    const T* begin() const{
        return dat;
    }
    const T* cbegin() const{
        return dat;
    }
    T* end(){
        return & dat[N];
    }
    const T* end() const{
        return & dat[N];
    }
    const T* cend() const{
        return & dat[N];
    }
    // Other ones are more tricky, I'm lazy


private: //========== Methods
    void checkRange(std::size_t i) {
        if (i >= N)
            throw std::out_of_range("MyArray");
    }

public: //========== Data
    /// Our data as built-in array
    T dat[N];
};

template<typename T, size_t N>
template<typename I>
void MyArray<T, N>::assign(I begin, I end)
{
    int i = 0;
    for (I it = begin; it != end; ++it, ++i)
        at(i) = *it;
}

// Non-member operator== definition
template<typename T1, size_t N1>
bool operator==(const MyArray<T1, N1> & lhs, const MyArray<T1, N1> & rhs) {
    for (size_t i = 0; i < N1; ++i)
        if (lhs.dat[i] != rhs.dat[i])
            return false;
    return true;
}
template<typename T, size_t N>
bool operator!=(const MyArray<T, N> & lhs, const MyArray<T, N> & rhs) {
    return ! (lhs == rhs);
}
