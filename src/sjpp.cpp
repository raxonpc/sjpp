#include "sjpp/sjpp.hpp"
#include <curl/curl.h>

namespace sjpp {
    
    size_t write_callback(char *ptr, size_t size, size_t count, void *userdata) {
        auto string_ptr = reinterpret_cast<std::string *>(userdata);

        string_ptr->append(ptr, count);
        return count;
    }

    std::pair<std::string, Code> download_url(const std::string &url) {
        CURL *handle = curl_easy_init();
        if (!handle) { // curl failed to initialize
            return {"", Code::curlInitFailed};
        }

        // TODO
        return {"", Code::ok};
    }

//    std::pair<std::vector<Entry>, Code>
//    get_entries(std::string_view word) {}
} // namespace sjpp
