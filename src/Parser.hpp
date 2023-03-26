#pragma once

#include "sjpp/types.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace sjpp {

class Parser {
  public:
    enum class State {
        start, //!< at the beginning, before reaching "word", "znaczenie:", etc.
        word,  //!< after <h1> (it always contains the word)
        allowed,  //!< after <p>(nie)dopuszczalne w grach </p>
        meaning,  //!< after "znaczenie:"
        comments, //!< after "KOMENTARZE"
    };

    /*
     * provides info if the line search functions "find_XXX" succeeded
     */
    enum class FindCode {
        found,
        found_comment, //!< when searching for a word and the comment section
                       //!< begins
        not_found
    };

    enum class ParseCode {
        success,
        empty, // e.g. when the content of a <p> is empty
        invalid,
    };

  public:
    explicit Parser(const std::string& html);
    Parser() = default;

    std::pair<std::vector<Entry>, Code> parse() noexcept;

  private:
    // these functions return the whole line
    std::pair<std::string, FindCode> find_name() noexcept;
    std::pair<std::string, FindCode> find_next_line() noexcept;
    std::pair<std::string, FindCode> find_meaning() noexcept;

    static std::pair<std::string, Parser::ParseCode>
    get_tag_content(const std::string& line) noexcept;
    static std::pair<std::vector<std::string>, Parser::ParseCode>
    parse_meanings(const std::string& content) noexcept;
    static void remove_substr(std::string& line,
                              const std::string& substr) noexcept;

  private:
    std::stringstream m_html{};
    std::string m_current_word{};
    bool m_current_allowed{};
    State m_state{State::start};
};
} // namespace sjpp
