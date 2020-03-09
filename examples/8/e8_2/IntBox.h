#pragma once

#include <iostream>
#include <string>

/// Stores an int data in the heap using new, delete
class IntBox{
    friend std::ostream & operator<<(std::ostream & os, const IntBox & ib) noexcept;
    friend void swap(IntBox &lhs, IntBox &rhs) noexcept;
public:
    /// Empty Ctor
    IntBox() {
        std::cout << "Empty Ctor !" << std::endl;
    }

    /// Ctor, creates a heap object
    IntBox(int n) :
        data(new int(n)) {
        std::cout << "Ctor : " << n << std::endl;
    }


    /// Check if empty
    bool empty() noexcept {
        return data != nullptr;
    }

    /// bool cast for NOT empty
    explicit operator bool()  noexcept {
        return data == nullptr;
    }

    /// Set int value
    void setValue(int n) {
        if (data)
            *data = n;
        else
            data = new int(n);
    }

    /// Get int value
    int getValue() {
        if (data)
            return *data;
        else
            throw std::logic_error("IntBox::getValue() empty box");
    }

    /// Make empty
    void clear(){
        if (data) {
            delete data;
            data = nullptr;
        }
    }
    //========= Dtor, Copy and Move : The Rule Of 5

    /// Dtor, important !
    ~IntBox(){

        std::cout << "Dtor : " << dataStr() << std::endl;
        // Delete only if not nullptr !
        if (data)
            delete data;
    }

    /// Move ctor
    IntBox(IntBox && rhs) {
        data = rhs.data;  // Copy the pointer
        rhs.data = nullptr;  // Set rhs to empty without delete
        std::cout << "Move Ctor : " << dataStr() << std::endl;
    }

    /// Move assignment
    IntBox & operator=(IntBox && rhs) {
        if (this != &rhs) { // Check for self-assign
            clear(); // Clear self first
            data = rhs.data;  // Copy the pointer
            rhs.data = nullptr;  // Set rhs to empty without delete
        }
        std::cout << "Move assign : " << dataStr() << std::endl;
        return *this;
    }

    /// Copy Ctor : Deep Clone
    IntBox(const IntBox & rhs) {
        if (rhs.data) { // If rhs is not empty
            data = new int(*rhs.data);  // Deep clone the heap object
        }
        std::cout << "Copy Ctor : " << dataStr() << std::endl;
    }

    /// Copy assignment : Deep Clone
    IntBox & operator=(const IntBox & rhs) {
        if (this != &rhs) { // Check for self-assign
            clear(); // Clear self first
            if (rhs.data) { // If rhs is not empty
                data = new int(*rhs.data);  // Deep clone the heap object
            }
        }
        std::cout << "Copy assign : " << dataStr() << std::endl;
        return *this;
    }

private:

    /// Data to string
    std::string dataStr() const{
        if (data)
            return std::to_string(*data);
        else
            return "EMPTY";
    }

    /// Pointer to data, nullptr if empty
    int * data = nullptr;
};

std::ostream & operator<<(std::ostream & os, const IntBox & ib) noexcept {
    os << ib.dataStr();
    return os;
}

/// Efficient swap
void swap(IntBox &lhs, IntBox &rhs) noexcept {
    using std::swap;
    swap(lhs.data, rhs.data); // Swap pointers
}
