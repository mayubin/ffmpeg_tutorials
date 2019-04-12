//
// Created by wangrl on 19-4-12.
//
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>


struct Base {
    virtual void bar() { std::cout << "Base::bar\n"; }
    virtual ~Base() = default;
};

struct Derived : Base {
    Derived() { std::cout << "Drive::Drive\n"; }
    ~Derived() { std::cout << "Drive::~Drive\n"; }
    void bar() override {
        std::cout << "Drive::bar\n";
    }
};

void close_file(std::FILE *fp) {
    std::fclose(fp);
}

// a function consuming a unique_ptr can take it by value or by rvalue reference
std::unique_ptr<Derived> pass_through(std::unique_ptr<Derived> p) {
    p->bar();
    return p;
}

int main(int argc, char *argv[]) {
    std::cout << "unique ownership semantics demo\n";

    {
        auto p = std::make_unique<Derived>();   // p is a unique_ptr that owns a Drive
        auto q = pass_through(std::move(p));
        assert(!p);         // now p owns nothing and holds a null pointer
        q->bar();
    }

    std::cout << "Runtime polymorphism demo\n";
    {
        std::unique_ptr<Base> p = std::make_unique<Derived>();        // p is a unique_ptr that owns a Drive
                                                                    // as a pointer to base
        p->bar();       // virtual dispatch

        std::vector<std::unique_ptr<Base>> v;       // unique_ptr can be stored in a container
        v.push_back(std::make_unique<Derived>());
        v.push_back(std::move(p));
        v.emplace_back(new Derived);

        for (auto& p : v) p->bar();     // virtual dispatch
    }       // ~D called 3 times

    std::cout << "Custom deleter demo\n";
    std::ofstream("demo.txt") << 'x';   // prepare the file to read
    {
        std::unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("demo.txt", "r"), &close_file);

        if(fp) // fopen could have failed; in which case fp holds a null pointer
            std::cout << (char)std::fgetc(fp.get()) << '\n';
    } // fclose() called here, but only if FILE* is not a null pointer
      // (that is, if fopen succeeded)

    std::cout << "Custom lambda-expression deleter demo\n";
    {
        std::unique_ptr<Derived, std::function<void(Derived*)>> p(new Derived, [](Derived* ptr) {
            std::cout << "destroying from a custom deleter...\n";
            delete ptr;
        });     // p owns Drive
        p->bar();
    }   // the lambda above is called and Drive is destroyed

    std::cout << "Array form of unique_ptr demo\n";
    {
        std::unique_ptr<Derived[]> p{new Derived[3]};
    }   // calls ~Drive 3 times
}

