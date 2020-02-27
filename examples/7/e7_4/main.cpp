// Example 7.4 : File streams : ifstream, ofstream 
// Created by Oleksiy Grechnyev 2017

#include <iostream>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//==============================
// Copy with get(), put()
void copy1(istream & in, ostream & out){
    char c;
    while (in.get(c))
        out.put(c);
}
//==============================
// Copy with getline(), << Text only !!!
void copy2(istream & in, ostream & out){
    string s;
    while (getline(in, s))
        out << s << endl;
}
//==============================
// Copy with read(), write()
void copy3(istream & in, ostream & out){
    constexpr streamsize SIZE = 1024;
    char buf[SIZE];
    streamsize count;

    do {
        in.read(buf, SIZE);     // Read up to SIZE chars to the buffer
        count = in.gcount();    // Get the actual count
        out.write(buf, count);   // Write count chars
    } while (count > 0);        // Exit if count == 0
}
//==============================
// Copy with C files : fgetc(), fputc() :
// Note : C file objects are FILE*, not FILE !
void copy4(FILE * in, FILE * out){
    int i; // int, not char !
    while ((i = fgetc(in)) != EOF)
        fputc(i, out);
}
//==============================
// Copy with C files : fread(), fwrite() :
void copy5(FILE * in, FILE * out){
    constexpr size_t SIZE = 1024;
    char buf[SIZE];
    size_t count;

    while ( (count = fread(buf, 1, SIZE, in)) > 0)     // Read up to SIZE chars to the buffer
        fwrite(buf, 1, count, out);                    // Write count chars
}
//==============================
int main(){

    {
        cout << "File append :" << endl;
        ofstream out("append.txt", ios::out | ios::app);

        out << "Eddie lives... somewhere in time!" << endl;
    }

    {
        cout << "Copy with get(), put() :" << endl;

        // Binary mode is needed for binary files, otherwise problem with EOLs in Windows
        ifstream in1("infiles/text.txt", ios::in|ios::binary);
        ofstream out1("text1.txt", ios::out|ios::binary);
        copy1(in1, out1);

        ifstream in2("infiles/binary.bin", ios::in|ios::binary);
        ofstream out2("binary1.bin", ios::out|ios::binary);
        copy1(in2, out2);
    }
    

    {
        cout << "Copy with getline(), << (text only) :" << endl;

        // Binary mode is needed for binary files, otherwise problem with EOLs in Windows
        ifstream in1("infiles/text.txt");
        ofstream out1("text2.txt");
        copy2(in1, out1);  // A text-only copy !!!
    }


    {
        cout << "Copy with read(), write() :" << endl;

        // Binary mode is needed for binary files, otherwise problem with EOLs in Windows
        ifstream in1("infiles/text.txt", ios::in|ios::binary);
        ofstream out1("text3.txt", ios::out|ios::binary);
        copy3(in1, out1);

        ifstream in2("infiles/binary.bin", ios::in|ios::binary);
        ofstream out2("binary3.bin", ios::out|ios::binary);
        copy3(in2, out2);
    }

    {
        cout << "Copy with  C files : fgetc(), fputc() :" << endl;
        // FILE* (not FILE) is the variable to hold a C file
        FILE * in1 = fopen("infiles/text.txt", "rb");  // Read binary
        FILE * out1 = fopen("text4.txt", "wb");  // Write binary
        copy4(in1, out1);
        fclose(in1);  // You must always close C files !!!
        fclose(out1);

        FILE * in2 = fopen("infiles/binary.bin", "rb");  // Read binary
        FILE * out2 = fopen("binary4.bin", "wb");  // Write binary
        copy4(in2, out2);
        fclose(in2);  // You must always close C files !!!
        fclose(out2);
    }


    {
        cout << "Copy with  C files : fread(), fwrite() :" << endl;

        FILE * in1 = fopen("infiles/text.txt", "rb");  // Read binary
        FILE * out1 = fopen("text5.txt", "wb");  // Write binary
        copy4(in1, out1);
        fclose(in1);  // You must always close C files !!!
        fclose(out1);

        FILE * in2 = fopen("infiles/binary.bin", "rb");  // Read binary
        FILE * out2 = fopen("binary5.bin", "wb");  // Write binary
        copy5(in2, out2);
        fclose(in2);  // You must always close C files !!!
        fclose(out2);
    }


    return 0;
}
