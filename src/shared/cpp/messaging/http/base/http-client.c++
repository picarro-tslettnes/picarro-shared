/// -*- c++ -*-
//==============================================================================
/// @file http-client.h++
/// @brief HTTP requests using `cURLpp`
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "http-client.h++"
#include "platform/symbols.h++"
#include "platform/init.h++"
#include "status/exceptions.h++"
#include "logging/logging.h++"
#include "thread/signaltemplate.h++"

#include <curl/curl.h>

namespace shared::http
{
    HTTPClient::HTTPClient(const std::string &base_url)
        : base_url_(base_url),
          handle_(curl_easy_init())
    {
    }

    HTTPClient::~HTTPClient()
    {
        curl_easy_cleanup(this->handle_);
    }

    void HTTPClient::global_init()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }

    void HTTPClient::global_cleanup()
    {
        curl_global_cleanup();
    }

    std::string HTTPClient::base_url() const
    {
        return this->base_url_;
    }

    std::stringstream HTTPClient::get(const std::string &location) const
    {
        std::stringstream content;
        this->get(location, nullptr, nullptr, nullptr, &content, true);
        return content;
    }

    std::stringstream HTTPClient::get(const std::string &location,
                                      const std::string &expected_content_type) const
    {
        std::string content_type;
        std::stringstream stream;
        this->get(location, nullptr, &content_type, nullptr, &stream, true);
        str::tolower(&content_type);
        if (content_type != str::tolower(expected_content_type))
        {
            throw exception::FailedPostcondition(
                "Content type mismatch",
                {
                    {"location", location},
                    {"expected-content-type", expected_content_type},
                    {"received-content-type", content_type},
                });
        }

        return stream;
    }

    bool HTTPClient::get(const std::string &location,
                         ResponseCode *response_code,
                         std::string *content_type,
                         std::ostream *header_stream,
                         std::ostream *content_stream,
                         bool fail_on_error) const
    {
        ResponseCode response = 0;
        CURLcode code = curl_easy_setopt(this->handle_, CURLOPT_URL, location.c_str());

        if (code == CURLE_OK)
        {
            code = curl_easy_setopt(this->handle_, CURLOPT_WRITEFUNCTION, HTTPClient::receive);
        }

        if ((code == CURLE_OK) && (header_stream != nullptr))
        {
            code = curl_easy_setopt(this->handle_, CURLOPT_HEADERDATA, header_stream);
        }

        if (code == CURLE_OK)
        {
            code = curl_easy_setopt(this->handle_, CURLOPT_WRITEDATA, content_stream);
        }

        if ((code == CURLE_OK) && fail_on_error)
        {
            code = curl_easy_setopt(this->handle_, CURLOPT_FAILONERROR, 1L);
        }

        if (code == CURLE_OK)
        {
            code = curl_easy_perform(this->handle_);
        }

        if (code == CURLE_OK)
        {
            code = curl_easy_getinfo(this->handle_, CURLINFO_RESPONSE_CODE, &response);
            if (response_code)
            {
                *response_code = response;
            }
        }

        if ((code == CURLE_OK) && content_type)
        {
            char *ctype = nullptr;
            code = curl_easy_getinfo(this->handle_, CURLINFO_CONTENT_TYPE, &ctype);
            content_type->assign(ctype ? ctype : "");
        }

        if (code != CURLE_OK)
        {
            throw exception::FailedPostcondition(
                curl_easy_strerror(code),
                {
                    {"location", location},
                    {"curl_code", code},
                    {"response_code", response},
                });
        }

        return this->successful_response(response);
    }

    ResponseCode HTTPClient::put(const std::string &location,
                                 std::ostream *stream) const
    {
        return 0;
    }

    size_t HTTPClient::receive(char *ptr, size_t item_size, size_t num_items, void *userdata)
    {
        auto *ss = reinterpret_cast<std::ostream *>(userdata);
        ssize_t size = item_size * num_items;
        ss->write(ptr, size);
        return ss->good() ? size : 0;
    }

    bool HTTPClient::decompose_header(const std::string &text, Header *header)
    {
        static std::regex rx(
            "(\\w[^\\s:]*):\\s*"                      // (1) field name
            "([^\\r\\n]+"                             // (2) initial content line
            "(?:(?:\\r\\n|\\r|\\n)\\s+[^\\r\\n]+)*)"  // +(2) additional content lines
            "(?:\\r\\n|\\r|\\n)"                      // trailing newline
        );

        auto matchit = std::sregex_iterator(text.begin(), text.end(), rx);
        uint endpos = 0;
        for (std::sregex_iterator endit; matchit != endit; matchit++)
        {
            header->emplace(matchit->str(1), matchit->str(2));
            endpos = matchit->position(0) + matchit->length(0);
        }
        return str::strip(text.substr(endpos)).empty();
    }

    bool HTTPClient::successful_response(ResponseCode code)
    {
        switch (code / 100)
        {
        case 1:  // 1xx - informational responses
        case 2:  // 2xx - successul responses
            return true;

        case 3:  // 3xx - redirection responses
        case 4:  // 4xx - client error responses
        case 5:  // 5xx - server side responses
            return false;

        default:
            return false;
        }
    }

    static platform::InitTask init_http_client(
        "init_http_client",
        HTTPClient::global_init);

    static platform::ExitTask cleanup_http_client(
        "cleanup_http_client",
        HTTPClient::global_cleanup);
}  // namespace shared::http
