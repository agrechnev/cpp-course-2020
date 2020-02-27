// Example 7.5 : std::filesystem
// Created by Oleksiy Grechnyev 2020
// Note : filesystem crashes on uuntu gcc 8.x, try gcc 9.x instead !

#include <iostream>
#include <filesystem>


//==============================
int main(){
    using namespace std;

    // Create a path
    filesystem::path p("."); // Current directory
    
    
    cout << "p = " << p << endl;
    // Check that it exists
    cout << "filesystem::exists(p) = " << filesystem::exists(p) << endl;
    // Check that it is a directory
    cout << "filesystem::is_directory(p) = " << filesystem::is_directory(p) << endl;
    // Convert it to absolute, if needed
    cout << "filesystem::absolute(p) = " << filesystem::absolute(p) << endl;
    // Convert path to std::string
    cout << "p.string() = " << p.string() << endl;
    
    // Print the current directory
    cout << "\nCurrent directory:" << endl;
    for (const filesystem::directory_entry &de : filesystem::directory_iterator(p)) {
        cout << de.path() << endl;
    }
    
    // Create a new path
    // Note: overloaded / operator !
    filesystem::path p2 = p / "newdir";
    cout << "p2 = " << p2 << endl;
    cout << "filesystem::exists(p2) = " << filesystem::exists(p2) << endl;  // Does not exist !
    // Create directory
    filesystem::create_directory(p2);
    
    return 0;
}
