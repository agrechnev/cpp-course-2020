// Example 6.8 : RapidJSON
// Created by Oleksiy Grechnyev 2020

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

//==============================
int main(){
    using namespace std;
    
    ifstream inFile("hero.json");   // Open json file
    rapidjson::IStreamWrapper isw(inFile); // Create rapidjson wrapper
    // Note: According to rapidjson docs, it's faster to use C FILE instead of C++ streams!
    rapidjson::Document d; // Create the document
    // Parse the stream
    if (d.ParseStream(isw).HasParseError()) 
            throw runtime_error("Parse Error !");
    
    // Work with individual fields
    // In real projects, always perform these checks !
    // Otherwise rapidjson quits on error !!!
    // I guess one could define RAPIDJSON_ASSERT to throw exceptions instead
    // Note d["name"] has type of rapidjson::Value ! There is a DOM tree of Value objects.
    // Document is a child of Value apparently.
    if (d.HasMember("name") && d["name"].IsString())
        cout << "name = " << d["name"].GetString() << endl;
    
    // Note: int and double are strictly different !
    if (d.HasMember("age") && d["age"].IsInt())
        cout << "age = " << d["age"].GetInt() << endl;
    else if (d.HasMember("age") && d["age"].IsDouble())
        cout << "age = " << d["age"].GetDouble() << endl;
        
    if (d.HasMember("weapons") && d["weapons"].IsArray()) {
        cout << "weapons =\n";
        for (const rapidjson::Value & v : d["weapons"].GetArray() ) {
            if (v.IsString())
                cout << v.GetString() << endl;
        }
    }
    
    // RapidJSON can do many other things, including Sax and JSON-creation !
    
    return 0;
}
