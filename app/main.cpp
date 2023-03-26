#include "sjpp/sjpp.hpp"
#include <iostream>

int main() {
    sjpp::SjpAPI sjp{};

    auto [entries, code] = sjp.get_entries("krowa");

    if(code != sjpp::Code::ok) {
        std::cerr << "Error looking up the word in the dictionary\n";
        return 1;
    }

    for (const auto &entry: entries) {
        std::cout << entry.word << ": " << entry.meaning << '\n';
    }
}
