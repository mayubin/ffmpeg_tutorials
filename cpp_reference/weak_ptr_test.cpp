//
// Created by wangrl on 19-4-12.
//

#include <iostream>
#include <memory>

std::weak_ptr<int> gw;

void observe() {
    std::cout << "use_count == " << gw.use_count() << ": ";
    if (auto spt = gw.lock())   {   // has to be copied into a shared_ptr before usage
        std::cout << *spt << "\n";
    } else {
        std::cout << "gw is expired\n";
    }
}

int main(int argc, char *argv[]) {
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;

        observe();
    }
    observe();
}

