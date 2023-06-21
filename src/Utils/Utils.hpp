#pragma once

#include <string>

#include <userver/server/http/http_request.hpp>

namespace vkpg {

namespace Utils {

int GetLimit(const userver::server::http::HttpRequest& request, int def = 100);

bool GetDesc(const userver::server::http::HttpRequest& request,
             bool def = false);

std::string GetSinceStr(const userver::server::http::HttpRequest& request,
                        std::string def = "");

int GetSinceInt(const userver::server::http::HttpRequest& request, int def = 0);

}  // namespace Utils

}  // namespace vkpg
