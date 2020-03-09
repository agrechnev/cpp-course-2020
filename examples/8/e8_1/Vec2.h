#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <cmath>

// Note: noexcept is always a good idea unless you expect exceptions

/// Vec2 : a vector of two doubles x, y. Demonstrates operator overloading.
class Vec2{
    // ========= Friend operators
    // Only non-mmber operators which use private fields are included !
    friend bool operator==(const Vec2 & lhs, const Vec2 & rhs) noexcept ;
    friend std::ostream & operator<< (std::ostream & os, const Vec2 & v);
    friend std::istream & operator>> (std::istream & is, Vec2 & v);
    friend bool operator<(const Vec2 & lhs, const Vec2 & rhs) noexcept ;

public: //===== Methods
    /// xy ctor
    Vec2(double x, double y) : x(x), y(y) {}

    /// Default ctor
    Vec2() = default;

    /// Length of a vector
    double len(){
        return std::sqrt(x*x + y*y);
    }

    // Getters, setters
    double getX() const {
        return x;
    }

    void setX(double value) {
        x = value;
    }

    double getY() const {
        return y;
    }

    void setY(double value) {
        y = value;
    }

public: //====== Member operators
    // Compound assignments modify object and return ref to self (*this)
    Vec2 & operator+= (const Vec2 & rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Vec2 & operator-= (const Vec2 & rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    /// Multiply or divide vector by a double
    Vec2 & operator*= (double rhs) noexcept {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    Vec2 & operator/= (double rhs) noexcept {
        x /= rhs;
        y /= rhs;
        return *this;
    }
    // Increment and decrement
    // Not really needed for Vec2, but it's a demo !
    // Prefix first, return ref to self !
    Vec2 & operator++() noexcept {
        ++x;  // Increase both x, y by 1
        ++y;
        return *this; // Return self
    }
    Vec2 & operator--() noexcept {
        --x;  // Decrease both x, y by 1
        --y;
        return *this; // Return self
    }
    // Postfix versions have a fake (int) argument, return a copy by value
    Vec2 operator++(int) noexcept {
        Vec2 temp{*this};  // Make a copy
        operator++();  // Call prefix like this
        return temp; // Return the copy
    }
    Vec2 operator--(int) noexcept {
        Vec2 temp{*this};  // Make a copy
        --*this;  // Or call prefix like this
        return temp; // Return the copy
    }
    // The [] operator, we need both const and non-const version
    double & operator[] (int i){
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw std::out_of_range("Vec2::operator[]");
        }
    }
    // Could have returned double by value here, but let's show the classical way
    const double & operator[] (int i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw std::out_of_range("Vec2::operator[] const");
        }
    }
    // Function-call operator (not needed for Vec2, just for fun), prints stuff
    void operator()(const std::string &s) noexcept  {
        std::cout << s << *this << std::endl;
    }
    // Cast to double
    explicit operator double() noexcept {
        return len();
    }
    // Cast to bool (explicit works in if, ?:)
    explicit operator bool() noexcept {
        return x || y;
    }

private: //===== Data
    double x = std::nan("");
    double y = std::nan("");
};  // End of class Vec2

//------------------------------------------------------
// Nom-member operators :
//------------------------------------------------------
//------------------------------------------------------
//  == and != : should be consistent

inline bool operator==(const Vec2 & lhs, const Vec2 & rhs)  noexcept {
    if (&lhs == &rhs)  // Optional, check if the same object
        return true;
    else
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

inline bool operator!=(const Vec2 & lhs, const Vec2 & rhs)  noexcept {
    return !(lhs == rhs);   // The proper way to define !=
}
//------------------------------------------------------
// <<, >> with io streams
// Here I don't use noexcept as io streams might throw
inline std::ostream & operator<< (std::ostream & os, const Vec2 & v){
    os << std::setw(10) << v.x << " " << std::setw(10) << v.y;  // No endl !
    return os;
}

inline std::istream & operator>> (std::istream & is, Vec2 & v) {
    is >> v.x >> v.y;
    if (!is)
        v = Vec2();   // Default (NaN) vector on IO error
    return is;
}
//------------------------------------------------------
// Overloading <, >, <=, >=, should be consistent with each other and ==
// For a good definition, either a<b, or b>a, or a==b
// Also a<b is the same as b>a etc.
inline bool operator<(const Vec2 & lhs, const Vec2 & rhs) noexcept  {
    // You have to choose importance here
    // In our example, x is more important that y
    if (lhs.x == rhs.x)
        return lhs.y < rhs.y;
    else
        return lhs.x < rhs.x ;
}
// The remaining 3 operators are defined via <
inline bool operator>(const Vec2 & lhs, const Vec2 & rhs) noexcept {
    return rhs < lhs;
}
inline bool operator<=(const Vec2 & lhs, const Vec2 & rhs) noexcept  {
    return !(lhs > rhs);   // Like this
}
inline bool operator>=(const Vec2 & lhs, const Vec2 & rhs) noexcept  {
    return !(lhs < rhs);
}
//------------------------------------------------------
// Overloading +, -, *, / should be based on += etc.
// They return Vec2 BY VALUE as it is a new object
inline Vec2 operator+(const Vec2 & lhs, const Vec2 & rhs) noexcept {
    Vec2 temp = lhs;    // Make a copy
    temp += rhs;
    return temp;
}
// This can be simplified by passing lhs by value and removing temp
inline Vec2 operator-(Vec2 lhs, const Vec2 & rhs) noexcept {
    lhs -= rhs;
    return lhs;
}
inline Vec2 operator*(Vec2 lhs, double rhs) noexcept {
    lhs *= rhs;
    return lhs;
}
// We need the opposite direction operator* too
inline Vec2 operator*(double lhs, const Vec2 & rhs) noexcept {
    return rhs*lhs;
}
// Don't forget the divide
inline Vec2 operator/(Vec2 lhs, double rhs) noexcept {
    lhs /= rhs;
    return lhs;
}
// Finally, the unary - :
inline Vec2 operator-(const Vec2 & v) noexcept {
    return v*(-1.0);
}
