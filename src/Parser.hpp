#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "sjpp/types.hpp"

namespace sjpp {

    class Parser {
    public:
        enum class State {
            start, //!< at the beginning, before reaching "word", "znaczenie:", etc.
            word, //!< after <h1> (it always contains the word)
            allowed, //!< after <p>(nie)dopuszczalne w grach </p>
            meaning, //!< after "znaczenie:"
            comments, //!< after "KOMENTARZE"
        };

        /*
         * provides info if the line search functions "find_XXX" succeeded
         */
        enum class LineCode {
            found,
            found_comment, //!< when searching for a word and the comment section begins
            not_found
        };

    public:
        explicit Parser(const std::string &html);
        Parser() = default;

        std::pair<std::vector<Entry>, Code> parse() noexcept;

    private:
        std::stringstream m_html{};
        std::string m_current_word{};
        bool m_current_allowed{};
        State m_state{State::start};

        // these functions return the whole line
        std::pair<std::string, LineCode> find_name() noexcept;
    };
} // sjpp
