#include "Parser.hpp"
#include <utility>
#include <cstddef>
#include <algorithm>

namespace sjpp {
    Parser::Parser(const std::string &html) : m_html{html} {
    }

    std::pair<std::string, Parser::FindCode> Parser::find_name() noexcept {
        std::string line{};

        while (m_html) {
            std::getline(m_html, line);

            if (line.starts_with("<h1")) { // found name of the word
                return {line, FindCode::found};
            } else if (line.find("KOMENTARZE") != std::string::npos) { // found comments
                return {line, FindCode::found_comment};
            }
        }

        return {"", FindCode::not_found};
    }

    std::pair<std::string, Parser::FindCode> Parser::find_meaning() noexcept {
        std::string line{};

        while (m_html) {
            std::getline(m_html, line);

            if(line.find("znaczenie:") != std::string::npos) {
                return { line, FindCode::found };
            }
        }

        return {"", FindCode::not_found};
    }

    std::pair<std::string, Parser::FindCode> Parser::find_next_line() noexcept {
        if(!m_html) {
            return { "", FindCode::not_found };
        }
        std::string line{};
        std::getline(m_html, line);
        return { line, FindCode::found };
    }

    // To get what's inside <tag></tag>
    std::pair<std::string, Parser::ParseCode> Parser::get_tag_content(const std::string& line) noexcept {
        auto left = line.find('>');
        if(left == std::string::npos) {
            return { "", ParseCode::invalid };
        }
        auto right = line.find('<', left);
        if(right == std::string::npos) {
            return { "", ParseCode::invalid };
        }

        if(right - left == 1) {
            return { "", ParseCode::empty };
        }

        auto word = line.substr(left + 1, right - left - 1);
        return { word, ParseCode::success };
    }

    void Parser::remove_substr(std::string& line, const std::string& substr) noexcept {
        auto n = substr.length();
        for (auto i = line.find(substr); i != std::string::npos; i = line.find(substr))
            line.erase(i, n);
    }

    std::pair<std::vector<std::string>, Parser::ParseCode> Parser::parse_meanings(const std::string& content) noexcept {
        if(content.size() <= 3) return { { content }, ParseCode::success };

        std::vector<std::string> meanings{};
        if(content[0] == '1') {
            std::size_t i = 0;
            while(true) {
                i = content.find(' ', i);
                if(i == std::string::npos) {
                    return {meanings, ParseCode::success};
                } else if(i + 1 == content.size()) {
                    return { meanings, ParseCode::invalid };
                }

                auto right = content.find(';', i);
                if(right == std::string::npos) {
                    meanings.push_back(content.substr(i + 1, content.size() - (i + 1)));
                }  else {
                    meanings.push_back(content.substr(i + 1, right - (i + 1)));
                }
                i = right;
            }
        } else {
            return { { content }, ParseCode::success };
        }
    }


    std::pair<std::vector<Entry>, Code> Parser::parse() noexcept {
        std::vector<Entry> output{};
        while (true) {
            switch (m_state) {
                // COMMENTS - we reached the end of the dictionary page
                // The comments section only consists of rude arguments
                case State::comments: {
                    if(output.size() == 1 ) {
                        if(output[0].meaning.empty()) {
                            return { output, Code::missingEntries };
                        }
                    }
                    return { output, Code::ok };
                }
                case State::start: {
                    auto [line, find_code] = find_name();
                    if (find_code == FindCode::found_comment) { // reached comments, successful parsing
                        m_state = State::comments;
                        continue;
                    } else if (find_code == FindCode::not_found) { // neither comments nor a word found, invalid file
                        return {output, Code::invalidFile};
                    }

                    auto [word, parse_code] = get_tag_content(line);
                    if (parse_code != ParseCode::success) {
                        return {output, Code::invalidFile};
                    }
                    m_current_word = word;
                    m_state = State::word;
                    break;
                }
                case State::word: {
                    auto [line, find_code] = find_next_line();
                    if(find_code != FindCode::found) {
                        return { output, Code::invalidFile };
                    }

                    auto [content, parse_code] = get_tag_content(line);
                    if(parse_code != ParseCode::success) {
                        return { output, Code::invalidFile };
                    }

                    if(content == "niedopuszczalne w grach ") {
                        m_current_allowed = false;
                    } else if(content == "dopuszczalne w grach ") {
                        m_current_allowed = true;
                    } else if(content == "nie występuje w słowniku") {
                        return { output, Code::wordNotFound };
                    } else {
                        return { output, Code::invalidFile };
                    }
                    m_state = State::allowed;
                    break;
                }
                case State::allowed: {
                    auto [line, find_code] = find_meaning();
                    if(find_code != FindCode::found) {
                        return { output, Code::invalidFile };
                    }
                    m_state = State::meaning;
                    break;
                }
                case State::meaning: {
                    auto [line, find_code] = find_next_line();
                    if(find_code != FindCode::found) {
                        return { output, Code::invalidFile };
                    }

                    remove_substr(line, "<br />");
                    auto [content, code] = get_tag_content(line);
                    if(code == ParseCode::empty) {
                        output.emplace_back(m_current_word, "", m_current_allowed);
                    }
                    auto [meanings, parse_code] = parse_meanings(content);
                    if(parse_code != ParseCode::success) {
                        return { output, Code::invalidFile };
                    }
                    std::transform(meanings.cbegin(),
                                   meanings.cend(),
                                   std::back_inserter(output),
                                   [this](const auto& meaning) {
                        return Entry{ m_current_word, meaning, m_current_allowed };
                    });
                    m_state = State::start;
                }
            }
        }
    }

} // sjpp