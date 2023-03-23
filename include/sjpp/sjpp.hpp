#pragma once

#include "types.hpp"
#include <vector>
#include <utility>

namespace sjpp {
    std::pair<std::vector<Entry>, Code>
    get_entries(std::string_view word);
} // namespace sjpp
