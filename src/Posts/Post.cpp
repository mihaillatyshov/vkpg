#include "Post.hpp"

#include <fmt/format.h>

namespace vkpg {

namespace Post {

userver::formats::json::Value MakeJson(int id,                    //
                                       int parent,                //
                                       std::string_view author,   //
                                       std::string_view message,  //
                                       bool isEdited,             //
                                       std::string_view forum,    //
                                       int thread,                //
                                       std::string_view created) {
  userver::formats::json::ValueBuilder builder;
  builder["id"] = id;
  builder["parent"] = parent;
  builder["author"] = author;
  builder["message"] = message;

  builder["isEdited"] = isEdited;
  builder["forum"] = forum;
  builder["thread"] = thread;

  std::string created_at = created.data();
  created_at[10] = 'T';
  created_at.push_back('Z');
  builder["created"] = created_at;

  return builder.ExtractValue();
}

userver::formats::json::Value MakeJson(const TypeInsertPG& post,   //
                                       std::string_view nickname,  //
                                       std::string_view forum) {
  return MakeJson(std::get<0>(post),  //
                  std::get<1>(post),  //
                  nickname,           //
                  std::get<2>(post),  //
                  std::get<3>(post),  //
                  forum,              //
                  std::get<4>(post),  //
                  std::get<5>(post));
}

}  // namespace Post

}  // namespace vkpg