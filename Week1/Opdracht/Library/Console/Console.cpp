#include "split-join.hpp"
#include <iostream>
#include <regex>
#include <vector>

//int main()
//{
//    std::cout << "Hello World!\n";
//}

int main() {
    // Split op basis van spatie
    std::string zin{ "In deze zin staan zes woorden." };
    std::vector<std::string> woorden{ sp::split(zin, " ") };
    for (const auto& woord : woorden) {
        std::cout << woord << '\n';
    }

    // Join met streepje
    std::cout << sp::join(woorden, "-") << '\n';

    // Split op basis van reguliere expressie
    std::string tekst{ "123.456,789#012" };
    std::regex pat{ R"([.,#])" }; // R"()" is een raw string
    for (const auto& deel : sp::split(tekst, pat)) {
        std::cout << deel << ' ';
    }
    std::cout << '\n';
}
