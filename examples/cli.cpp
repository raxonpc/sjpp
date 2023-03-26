#include <iostream>
#include <sjpp/sjpp.hpp>

int main() {
    sjpp::SjpAPI sjp{};
    std::cout << "Podaj słowo do sprawdzenia: ";
    std::string word{};
    std::cin >> word;

    auto [entries, code] = sjp.get_entries(word);
    if(code != sjpp::Code::ok) {
        std::cerr << "Błąd w sprawdzaniu słowa\n";
        return 1;
    }

    for(const auto& entry : entries) {
        std::cout << entry.word << ": " << entry.meaning << '\n';
    }

    return 0;
}
