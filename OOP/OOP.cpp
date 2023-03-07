#include <iostream>
#include <string>
#include <fstream>
#include <ranges>
#include <string_view>

#include "Dictionary.h"

namespace rv = std::ranges::views;
namespace ranges = std::ranges;

int main()
{
    std::fstream file("../../dict.txt", std::ios::out);

    if (file.bad())
        return 1;

    Dictionary dictionary({{"forest", "place with trees"}});

    for (const auto& [word, definition] : dictionary) {
        file << word << ":::" << definition << '\n';
    }

    file.close();
    file = std::fstream("../../dict.txt", std::ios::in);

    for (const auto& line : ranges::istream_view<std::string>(file)
        | rv::split("\n")
    ) {
        std::cout << ;
    }
}
