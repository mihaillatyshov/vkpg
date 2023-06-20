#include "Thread.hpp"

namespace vkpg {

namespace Thread {

userver::formats::json::Value MakeJson(int id,                    //
                                       std::string_view title,    //
                                       std::string_view message,  //
                                       std::string_view slug,     //
                                       int votes,                 //
                                       std::string_view author,   //
                                       std::string_view forum,    //
                                       std::string_view created) {
  userver::formats::json::ValueBuilder builder;
  builder["id"] = id;
  builder["title"] = title;
  builder["message"] = message;
  builder["slug"] = slug;
  builder["votes"] = votes;
  builder["author"] = author;
  builder["forum"] = forum;
  builder["created"] = created;
}

userver::formats::json::Value MakeJson(const TypePG& thread) {
  return MakeJson(std::get<0>(thread),  //
                  std::get<1>(thread),  //
                  std::get<2>(thread),  //
                  std::get<3>(thread),  //
                  std::get<4>(thread),  //
                  std::get<5>(thread),  //
                  std::get<6>(thread),  //
                  std::get<7>(thread));
}

}  // namespace Thread

}  // namespace vkpg