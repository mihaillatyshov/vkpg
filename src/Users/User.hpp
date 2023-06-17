#pragma once

#include <string>
#include <tuple>

#include <userver/formats/json.hpp>

namespace vkpg {

using UserTypePG = std::tuple<std::string,  // nickname
                              std::string,  // fullname
                              std::string,  // about
                              std::string   // email
                              >;

inline userver::formats::json::Value MakeUserJson(std::string_view nickname,
                                                  std::string_view fullname,
                                                  std::string_view about,
                                                  std::string_view email) {
  return userver::formats::json::MakeObject("nickname", nickname,  //
                                            "fullname", fullname,  //
                                            "about", about,        //
                                            "email", email);
}
}  // namespace vkpg