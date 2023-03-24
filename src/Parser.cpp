#include "Parser.hpp"
#include <utility>

namespace sjpp {
    Parser::Parser(const std::string &html) : m_html{html} {
    }

    std::pair<std::string, Parser::LineCode> Parser::find_name() noexcept {
        bool found = false;
        std::string line{};

        while (m_html) {
            std::getline(m_html, line);

            if (line.starts_with("<h1")) { // found name of the word
                return {line, LineCode::found};
            } else if (line.find("KOMENTARZE") != std::string::npos) { // found comments
                return {line, LineCode::found_comment};
            }
        }

        return {"", LineCode::not_found};
    }

    std::pair<std::vector<Entry>, Code> Parser::parse() noexcept {
        std::vector<Entry> output{};
        while (true) {
            switch (m_state) {
                case State::start: {
                    auto [line, code] = find_name();
                    if (code == LineCode::found_comment) { // reached comments, successful parsing
                        return {output, Code::ok};
                    } else if (code == LineCode::not_found) { // neither comments nor a word found, invalid file
                        return {output, Code::invalidFile};
                    }

                    m_state = State::word;

                    // auto [word, code] = parse_name(line);
                }
                default:
                    // TODO
                    return {output, Code::ok};
            }
        }
    }

} // sjpp