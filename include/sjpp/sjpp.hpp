/** \file sjpp.hpp
 * Main header file for sjpp API.
 */

#pragma once

#include "types.hpp"
#include <utility>
#include <vector>

namespace sjpp {

/**
 * The API class that does the lookups
 */
class SjpAPI {
  public:
    SjpAPI();

    ~SjpAPI();

    /**
     * The core function which does the dictionary lookup
     * @param word A string holding the word to look up/
     * @return The dictionary entries (if any) and an error code.
     */
    [[nodiscard]] std::pair<std::vector<Entry>, Code>
    get_entries(std::string_view word);

  private:
    struct Impl;
    Impl* m_impl;

    std::pair<std::string, Code> download_url(const std::string& url) noexcept;
};

} // namespace sjpp
