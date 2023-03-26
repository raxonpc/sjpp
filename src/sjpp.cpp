#include "sjpp/sjpp.hpp"
#include "Parser.hpp"
#include <curl/curl.h>
#include <algorithm>

namespace sjpp {
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


    size_t write_callback(char *ptr, size_t size, size_t count, void *userdata) {
        auto string_ptr = reinterpret_cast<std::string *>(userdata);

        string_ptr->append(ptr, count);
        return count;
    }

    std::pair<std::string, Code> SjpAPI::download_url(const std::string &url) noexcept {
        std::string content{};
        // configure CURL
        curl_easy_setopt(m_impl->m_handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_impl->m_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(m_impl->m_handle, CURLOPT_WRITEDATA, &content);
        CURLcode res = curl_easy_perform(m_impl->m_handle);

        switch (res) {
            case CURLE_OK:
                return {content, Code::ok};
            case CURLE_COULDNT_CONNECT:
            case CURLE_COULDNT_RESOLVE_HOST:
                return {"", Code::notConnected};
            default:
                return {"", Code::curlError};
        }
    }

    std::pair<std::vector<Entry>, Code> SjpAPI::get_entries(std::string_view word) {
        // construct a URL
        std::string sjp_url{"https://sjp.pl/"};
        sjp_url += word;

        // convert spaces to + signs
        std::replace(sjp_url.begin(), sjp_url.end(), ' ', '+');

        auto [content, code] = download_url(sjp_url);
        if (code != Code::ok) {
            return {{}, code};
        }

        Parser html_parser{ content };
        return html_parser.parse();
    }

} // namespace sjpp
