#pragma once

#include "types.hpp"
#include <vector>
#include <utility>

namespace sjpp {

    class SjpAPI {
    public:
        SjpAPI();

        ~SjpAPI();

        [[nodiscard]] std::pair<std::vector<Entry>, Code>
        get_entries(std::string_view word);

    private:
        struct Impl;
        Impl *m_impl;

        std::pair<std::string, Code> download_url(const std::string &url) noexcept;
    };


} // namespace sjpp
