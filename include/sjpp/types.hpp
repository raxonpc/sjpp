#pragma once

#include <string>

namespace sjpp {
    enum class Code {
        ok,             //!< success
        curlError,      //!< when libcurl failed for some other reason
        notConnected,   //!< could not establish connection
        wordNotFound,   //!< word does not exist in the dictionary
        missingEntries, //!< when the word exists in the dictionary, but there are no meanings
        invalidFile     //!< when html is not valid
    };

    struct Entry {
        Entry(const std::string& word, const std::string& meaning, bool allowed_in_games)
        : word{ word }, meaning{ meaning }, allowed_in_games{ allowed_in_games } {}


        std::string word{};
        std::string meaning{};
        bool allowed_in_games{};
    };

    class sjpp_exception : public std::exception {
    public:
        explicit sjpp_exception(const std::string &msg) : message{msg} {}

        explicit sjpp_exception(const char *msg) : message{msg} {}

        sjpp_exception(const sjpp_exception &other) : message{other.what()} {}


        [[nodiscard]] const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };

}


