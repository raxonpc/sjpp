#include "sjpp/sjpp.hpp"
#include <iostream>

int main() {
    sjpp::SjpAPI sjp{};

    auto [entries, code] = sjp.get_entries("krowa");

    for (const auto &entry: entries) {
        std::cout << entry.meaning << '\n';
    }
}
