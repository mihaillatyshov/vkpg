#include "User.hpp"

namespace vkpg {

namespace User {

userver::formats::json::Value MakeJson(std::string_view nickname,         //
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

userver::formats::json::Value MakeJson(const TypePG& user) {
  return MakeJson(std::get<0>(user),  //
                  std::get<1>(user),  //
                  std::get<2>(user),  //
                  std::get<3>(user));
}

userver::storages::postgres::ResultSet SelectByNickname(
    const userver::storages::postgres::ClusterPtr& cluster,
    std::string_view nickname) {
  return cluster->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      "SELECT nickname, fullname, about, email FROM tp.users "
      "WHERE lower(nickname) = ($1) ",
      nickname);
}

}  // namespace User

}  // namespace vkpg