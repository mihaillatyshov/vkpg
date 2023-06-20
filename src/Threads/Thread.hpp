#pragma once

#include <string>
#include <tuple>

#include <userver/formats/json.hpp>
#include <userver/storages/postgres/cluster.hpp>

namespace vkpg {

namespace Thread {

using TypePG = std::tuple<int,          // id
                          std::string,  // title
                          std::string,  // message
                          std::string,  // slug
                          int,          // votes
                          std::string,  // author (user nickname)
                          std::string,  // forum
                          std::string   // created
                          >;

userver::formats::json::Value MakeJson(int id,                    //
                                       std::string_view title,    //
                                       std::string_view message,  //
                                       std::string_view slug,     //
                                       int votes,                 //
                                       std::string_view author,   //
                                       std::string_view forum,    //
                                       std::string_view created);

userver::formats::json::Value MakeJson(const TypePG& thread);

userver::storages::postgres::ResultSet SelectBySlug(
    const userver::storages::postgres::ClusterPtr& cluster,
    std::string_view slug);

}  // namespace Thread

}  // namespace vkpg