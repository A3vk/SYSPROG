#include <iostream>
#include <mylib.hpp>

int main() {
    mylib::myclass obj {"Hello, world!"};
    std::cout << obj.message() << '\n';
}
