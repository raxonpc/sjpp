#include "sjpp/sjpp.hpp"
#include <curl/curl.h>

namespace sjpp {

    size_t write_callback(char *ptr, size_t size, size_t count, void *userdata) {
        auto string_ptr = reinterpret_cast<std::string *>(userdata);

        string_ptr->append(ptr, count);
        return count;
    }

    std::pair<std::string, Code> download_url(const std::string &url) {
//        CURL *handle = curl_easy_init();
//        if (!handle) { // curl failed to initialize
//            return {"", Code::curlInitFailed};
//        }

//        std::string content{};
//        // configure CURL
//        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
//        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
//        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &content);
//        CURLcode res = curl_easy_perform(handle);
//
//        curl_easy_cleanup(handle);
//
//        switch (res) {
//            case CURLE_OK:
//                return {content, Code::ok};
//            case CURLE_COULDNT_CONNECT:
//            case CURLE_COULDNT_RESOLVE_HOST:
//                return {"", Code::notConnected};
//            default:
//                return {"", Code::curlError};
//        }
    }

    struct SjpAPI::Impl {
        Impl() : m_handle{curl_easy_init()} {
            if (!m_handle) {
                throw sjpp_exception{"Failed initializing curl"};
            }
        }

        ~Impl() {
            curl_easy_cleanup(m_handle);
        }

        CURL *m_handle{nullptr};
    };


    SjpAPI::SjpAPI() : m_impl{new Impl{}} {
    }

    SjpAPI::~SjpAPI() {
        delete m_impl;
    }

    std::pair<std::vector<Entry>, Code> SjpAPI::get_entries(std::string_view word) {
        // TODO:
        return {{}, Code::ok};
    }

} // namespace sjpp
