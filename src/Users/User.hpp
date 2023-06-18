#pragma once

#include <string>
#include <tuple>

#include <userver/formats/json.hpp>
#include <userver/storages/postgres/cluster.hpp>

namespace vkpg {

namespace User {
using TypePG = std::tuple<std::string,                 // nickname
                          std::string,                 // fullname
                          std::optional<std::string>,  // about
                          std::string                  // email
                          >;

userver::formats::json::Value MakeJson(std::string_view nickname,         //
                                       std::string_view fullname,         //
                                       std::optional<std::string> about,  //
                                       std::string_view email);

userver::formats::json::Value MakeJson(const TypePG& user);

userver::storages::postgres::ResultSet SelectByNickname(
    const userver::storages::postgres::ClusterPtr& cluster,
    std::string_view nickname);

}  // namespace User

}  // namespace vkpg