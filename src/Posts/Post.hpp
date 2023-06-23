#pragma once

#include <string>
#include <tuple>

#include <userver/formats/json.hpp>
#include <userver/server/http/http_request.hpp>
#include <userver/storages/postgres/cluster.hpp>

namespace vkpg {

namespace Post {

using TypePG = std::tuple<int,          // id
                          int,          // parent
                          std::string,  // author
                          std::string,  // message
                          bool,         // isEdited
                          std::string,  // forum
                          int,          // thread
                          std::string   // created
                          >;

using TypeInsertPG = std::tuple<int,          // id
                                int,          // parent
                                std::string,  // message
                                bool,         // isEdited
                                int,          // thread
                                std::string   // created
                                >;

userver::formats::json::Value MakeJson(int id,                    //
                                       int parent,                //
                                       std::string_view author,   //
                                       std::string_view message,  //
                                       bool isEdited,             //
                                       std::string_view forum,    //
                                       int thread,                //
                                       std::string_view created);

userver::formats::json::Value MakeJson(const TypeInsertPG& post,   //
                                       std::string_view nickname,  //
                                       std::string_view forum);

}  // namespace Post

}  // namespace vkpg