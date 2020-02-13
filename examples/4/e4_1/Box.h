//  Created by Oleksiy Grechnyev 2020

/// A simple class template : A box holding a value
template <typename T>
class Box{
public: 
    /// Ctor
    Box(const T &val) : 
        val(val) {}
        
    /// Setter
    void setVal(const T &val) {
        Box::val = val;
    }
    
    /// Getter
    const T & getVal(){
        return val;
    }
        
private:
    /// The value
    T val;
};
