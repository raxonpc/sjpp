#pragma once

#include <string>

namespace sjpp {
    enum class Code {
        ok,             //!< success
        curlInitFailed, //!< libcurl failed to initialize
        notConnected,   //!< could not establish connection
        wordNotFound,   //!< word does not exist in the dictionary
        missingEntries, //!< when the word exists in the dictionary, but there are no meanings
    };

    struct Entry {
        std::string word{};
        std::string meaning{};
        bool allowed_in_games{};
    };

}


