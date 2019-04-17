//
// Created by wangrl on 19-4-17.
//


#include <string>
#include <iostream>

void double_string(std::string& s) {
    s += s;     // 's' is the same object as main()'s 'str'.
}

char& char_number(std::string& s, std::size_t n) {
    return s.at(n);         // string::at() return a reference to char.
}

int main(int argc, char *argv[]) {

    // Lvalue references
    // Lvalue references can be used to alias an existing object.
    {
        std::string s = "Ex";
        std::string& r1 = s;
        const std::string& r2 = s;

        r1 += "ample";      // modifies s
        // r2 += "!";       // error: cannot modify through reference to const
        std::cout << r2 << '\n';    // prints s, which now holds "Example"

    }

    // They can also be used to implement pass-by-reference semantics in function calls.
    {
        std::string str = "Test";
        double_string(str);
        std::cout << str << '\n';
    }

    // When a function's return type is lvalue reference, the function call expression
    // becomes an lvalue expression.
    {
        std::string str = "Test";
        char_number(str, 1) = 'a';      // the function call is lvalue, can be assigned to
        std::cout << str << '\n';
    }

    {
        std::string s1 = "Test";
        // std::string&& r1 = s1;       // error, can't bind to lvalue

        const std::string& r2 = s1 + s1;    // okay, lvalue reference to const extends lifetime
        // r2 += "Test";                // error: can't modify through reference to const

        std::string&& r3 = s1 + s1;     // okay: rvalue reference extends lifetime
        r3 += "Test";                   // okay: can modify through reference to non-const
        std::cout << r3 << '\n';
    }


}

