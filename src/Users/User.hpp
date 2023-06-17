#pragma once

#include <string>
#include <tuple>

#include <userver/formats/json.hpp>

namespace vkpg {

using UserTypePG = std::tuple<std::string,                 // nickname
                              std::string,                 // fullname
                              std::optional<std::string>,  // about
                              std::string                  // email
                              >;

inline userver::formats::json::Value MakeUserJson(
    std::string_view nickname,         //
    std::string_view fullname,         //
    std::optional<std::string> about,  //
    std::string_view email) {
  userver::formats::json::ValueBuilder builder;
  builder["nickname"] = nickname;
  builder["fullname"] = fullname;
  builder["email"] = email;
  if (about.has_value()) {
    builder["about"] = about.value();
  }
  return builder.ExtractValue();
}

}  // namespace vkpg